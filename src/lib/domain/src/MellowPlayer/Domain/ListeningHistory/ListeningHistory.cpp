#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/ListeningHistory/TimeLimits.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <QDateTime>
#include <QSet>
#include <QTimer>
#include <QVariant>
#include <algorithm>

using namespace MellowPlayer::Domain;

ListeningHistory::ListeningHistory(IListeningHistoryDatabase& model, IPlayer& player, Settings& settings)
        : _isEnabledSetting(settings.get(SettingKey::PRIVACY_ENABLE_LISTENING_HISTORY)),
          _limitSetting(settings.get(SettingKey::PRIVACY_LISTENING_HISTORY_LIMIT)),
          _logger(Loggers::logger("ListeningHistory")),
          _database(model),
          _player(player)
{
    connect(&player, &IPlayer::currentSongChanged, this, &ListeningHistory::onSongChanged);
    connect(&player, &IPlayer::playbackStatusChanged, this, &ListeningHistory::onPlaybackStatusChanged);
    connect(&_isEnabledSetting, &Setting::valueChanged, this, &ListeningHistory::onIsEnabledChanged);
    connect(&_limitSetting, &Setting::valueChanged, this, &ListeningHistory::clearOutdatedEntries);
}

void ListeningHistory::onPlaybackStatusChanged()
{
    addSong(_player.currentSong());
}

void ListeningHistory::onSongChanged(Song* song)
{
    addSong(song);
}

void ListeningHistory::addSong(Song* song)
{
    auto newEntry = ListeningHistoryEntry::fromData(song, _player.serviceName());
    addSong(song, newEntry);
}

void ListeningHistory::initialize()
{
    _database.initialize();
    _entries = _database.toList();
    clearOutdatedEntries();
}

QList<ListeningHistoryEntry> ListeningHistory::toList() const
{
    return _entries;
}

int ListeningHistory::count() const
{
    return toList().count();
}

void ListeningHistory::clear()
{
    _database.clear();
    updateRemovedEntries();
}

void ListeningHistory::removeById(int entryId)
{
    _database.remove("id", QString("%1").arg(entryId));
    updateRemovedEntries();
}

void ListeningHistory::removeByService(const QString& serviceName)
{
    _database.remove("serviceName", serviceName);
    updateRemovedEntries();
}

void ListeningHistory::removeManyById(const QList<int>& ids)
{
    _database.removeMany(ids);
    updateRemovedEntries();
}

void ListeningHistory::addSong(const Song* song, ListeningHistoryEntry& newEntry)
{
    if (!_isEnabledSetting.value().toBool())
        return;

    auto previousEntry = _previousEntryPerPlayer[_player.serviceName()];

    if (previousEntry.equals(newEntry) || !newEntry.isValid() || _player.playbackStatus() != PlaybackStatus::Playing)
        return;

    newEntry.id = _database.add(newEntry);
    _entries.append(newEntry);
    emit entryAdded(newEntry);
    _previousEntryPerPlayer[_player.serviceName()] = newEntry;
    LOG_DEBUG(_logger, "new entry: " + song->toString() + ", id=" + QString("%1").arg(newEntry.id));
}

void ListeningHistory::updateRemovedEntries()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    auto removedEntries = _entries.toSet().subtract(_database.toList().toSet()).values();
#else
    auto db = _database.toList();
    auto dbSet = QSet(db.begin(), db.end());
    auto removedEntries = QSet(_entries.begin(), _entries.end()).subtract(dbSet).values();
#endif
    for (auto entry : removedEntries)
    {
        int index = _entries.indexOf(entry);
        _entries.removeAt(index);
        emit entryRemoved(entry.id);
    }
}

void ListeningHistory::onIsEnabledChanged()
{
    if (!_isEnabledSetting.value().toBool())
        clear();
}

TimeLimits dateToTimeLimit(const QDateTime& dateTime)
{
    QDate date = dateTime.date();
    QDate today = QDateTime::currentDateTime().date();
    QDate yesterday = today.addDays(-1);
    QDate lastWeek = today.addDays(-7);
    QDate lastMonth = today.addMonths(-1);
    QDate lastYear = today.addYears(-1);

    if (date == today)
        return TimeLimits::Today;
    else if (date == yesterday)
        return TimeLimits::Yesterday;
    else if (date >= lastWeek)
        return TimeLimits::LastWeek;
    else if (date >= lastMonth)
        return TimeLimits::LastMonth;
    else if (date >= lastYear)
        return TimeLimits::LastYear;
    else
        return TimeLimits::Never;
}

void ListeningHistory::clearOutdatedEntries()
{
    TimeLimits limit = static_cast<TimeLimits>(_limitSetting.value().toInt());

    if (limit == TimeLimits::Never)
        return;

    LOG_INFO(_logger, "Cleaning history ");
    QString previousId;
    QList<int> items;
    for (auto entry : _entries)
    {
        TimeLimits entryLimit = dateToTimeLimit(entry.dateTime());
        // previous id is checked because we changed our appending rules, this is a workaround to
        // automatically clean listening history db that could contains many duplicate songs.
        if (entryLimit > limit || previousId == entry.songUniqueId)
        {
            items.append(entry.id);
            LOG_DEBUG(_logger, "Removing entry " << entry.songTitle);
        }
        previousId = entry.songUniqueId;
    }
    _database.removeMany(items);
    updateRemovedEntries();
}
