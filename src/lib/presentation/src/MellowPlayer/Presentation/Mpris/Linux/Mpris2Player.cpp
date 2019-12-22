#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Presentation/Mpris/Linux/Mpris2Player.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

const qlonglong Mpris2Player::SEC_TO_MICROSEC = 1000000;
const qlonglong Mpris2Player::SEEK_DELTA_LIMIT = Mpris2Player::SEC_TO_MICROSEC * 2;

Mpris2Player::Mpris2Player(IPlayer& player, ILocalAlbumArt& localAlbumArt, QObject* parent)
        : QDBusAbstractAdaptor(parent), _previousPosition(0), _logger(Loggers::logger("Mpris2Player")), _player(player), _localAlbumArt(localAlbumArt)
{
    connect(&player, &IPlayer::playbackStatusChanged, this, &Mpris2Player::onPlaybackStatusChanged);
    connect(&player, &IPlayer::currentSongChanged, this, &Mpris2Player::onSongChanged);
    connect(&player, &IPlayer::positionChanged, this, &Mpris2Player::onPositionChanged);
    connect(&player, &IPlayer::canSeekChanged, this, &Mpris2Player::onCanSeekChanged);
    connect(&player, &IPlayer::canGoNextChanged, this, &Mpris2Player::onCanGoNextChanged);
    connect(&player, &IPlayer::canGoPreviousChanged, this, &Mpris2Player::onCanGoPreviousChanged);
    connect(&player, &IPlayer::volumeChanged, this, &Mpris2Player::onVolumeChanged);

    connect(&localAlbumArt, &ILocalAlbumArt::urlChanged, this, &Mpris2Player::onArtUrlChanged);
}

QString Mpris2Player::playbackStatus()
{
    auto retVal = statusToString(_player.playbackStatus());
    LOG_TRACE(_logger, "playbackStatus() -> " + retVal);
    return retVal;
}

QString Mpris2Player::loopStatus()
{
    LOG_TRACE(_logger, "loopStatus() -> None");
    return "None";
}

void Mpris2Player::setLoopStatus(const QString&)
{
    LOG_TRACE(_logger, "setLoopStatus() not implemented");
}

bool Mpris2Player::shuffle()
{
    LOG_TRACE(_logger, "shuffle() -> false");
    return false;
}

void Mpris2Player::setShuffle(bool)
{
    LOG_TRACE(_logger, "setShuffle not implemented");
}

double Mpris2Player::volume()
{
    auto retVal = _player.volume();
    LOG_TRACE(_logger, "volume() -> " << retVal);
    return retVal;
}

void Mpris2Player::setVolume(double value)
{
    LOG_TRACE(_logger, "setVolume(" << value << ")");
    _player.setVolume(value);
}

QVariantMap Mpris2Player::metadata()
{
    LOG_TRACE(_logger, "metadata()");
    _lastMetadata = toXesam(*_player.currentSong());
    return _lastMetadata;
}

double Mpris2Player::minimumRate()
{
    LOG_TRACE(_logger, "minimumRate() -> 1.0");
    return 1.0;
}

double Mpris2Player::maximumRate()
{
    LOG_TRACE(_logger, "maximumRate() -> 1.0");
    return 1.0;
}

double Mpris2Player::rate()
{
    LOG_TRACE(_logger, "rate() -> 1.0");
    return 1.0;
}

void Mpris2Player::setRate(float)
{
    LOG_TRACE(_logger, "setRate() not implemented");
}

qlonglong Mpris2Player::position()
{
    auto pos = static_cast<qlonglong>(_player.position()) * SEC_TO_MICROSEC;
    LOG_TRACE(_logger, "position() -> " << pos);
    return pos;
}

bool Mpris2Player::canGoNext()
{
    auto retVal = _player.canGoNext();
    LOG_TRACE(_logger, "canGoNext() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canGoPrevious()
{
    auto retVal = _player.canGoPrevious();
    LOG_TRACE(_logger, "canGoPrevious() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canPlay()
{
    LOG_TRACE(_logger, "canPlay() -> true");
    return true;
}

bool Mpris2Player::canStop()
{
    LOG_TRACE(_logger, "canStop() -> false");
    return false;
}

bool Mpris2Player::canPause()
{
    LOG_TRACE(_logger, "canPause() -> true");
    return true;
}

bool Mpris2Player::canSeek()
{
    auto retVal = _player.canSeek();
    LOG_TRACE(_logger, "canSeek() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canControl()
{
    LOG_TRACE(_logger, "canControl() -> true");
    return true;
}

void Mpris2Player::PlayPause()
{
    LOG_TRACE(_logger, "PlayPause()");
    _player.togglePlayPause();
}

void Mpris2Player::Play()
{
    LOG_TRACE(_logger, "Play()");
    if (_player.playbackStatus() == Domain::PlaybackStatus::Paused || _player.playbackStatus() == Domain::PlaybackStatus::Stopped)
        _player.play();
}

void Mpris2Player::Pause()
{
    LOG_TRACE(_logger, "Pause()");
    if (_player.playbackStatus() == Domain::PlaybackStatus::Playing)
        _player.pause();
}

void Mpris2Player::Stop()
{
    LOG_TRACE(_logger, "Stop()");
    Pause();
}

void Mpris2Player::Next()
{
    LOG_TRACE(_logger, "Next()");
    _player.next();
}

void Mpris2Player::Previous()
{
    LOG_TRACE(_logger, "Previous()");
    _player.previous();
}

void Mpris2Player::Seek(qlonglong position)
{
    LOG_TRACE(_logger, "Seek(" << position << ")");
    qlonglong newPosition = this->position() + position;
    _previousPosition = 0;  // force emit seeked
    _player.seekToPosition(newPosition / SEC_TO_MICROSEC);
}

void Mpris2Player::SetPosition(const QDBusObjectPath&, qlonglong position)
{
    LOG_TRACE(_logger, "SetPosition(" << position << ")");
    _previousPosition = 0;  // force emit seeked
    _player.seekToPosition(position / SEC_TO_MICROSEC);
}

void Mpris2Player::onPlaybackStatusChanged()
{
    LOG_TRACE(_logger, "onPlaybackStatusChanged(" + playbackStatus() + ")");
    QVariantMap map;
    map["PlaybackStatus"] = statusToString(_player.playbackStatus());
    signalPlayerUpdate(map);
}

void Mpris2Player::onSongChanged(Song* song)
{
    LOG_TRACE(_logger, "onSongChanged()");
    if (song != nullptr)
    {
        QVariantMap map;
        map["Metadata"] = toXesam(*song);
        if (map != _lastMetadata)
            signalPlayerUpdate(map);
        _lastMetadata = map;
        connect(song, &Song::durationChanged, this, &Mpris2Player::onDurationChanged, Qt::UniqueConnection);
        connect(song, &Song::isFavoriteChanged, this, &Mpris2Player::onFavoriteChanged, Qt::UniqueConnection);
    }
}

void Mpris2Player::onFavoriteChanged()
{
    LOG_TRACE(_logger, "onFavoriteChanged()");
    onSongChanged(_player.currentSong());
}

void Mpris2Player::onArtUrlChanged()
{
    LOG_TRACE(_logger, "onArtUrlChanged()");
    onSongChanged(_player.currentSong());
}

void Mpris2Player::onPositionChanged()
{
    qlonglong pos = static_cast<qlonglong>(_player.position()) * SEC_TO_MICROSEC;
    if (labs(pos - _previousPosition) > SEEK_DELTA_LIMIT || (_previousPosition == 0 && pos > 0))
        emit Seeked(pos);
    _previousPosition = pos;
}

void Mpris2Player::onDurationChanged()
{
    LOG_TRACE(_logger, "onDurationChanged()");
    onSongChanged(_player.currentSong());
}

void Mpris2Player::onCanSeekChanged()
{
    LOG_TRACE(_logger, "onCanSeekChanged()");
    QVariantMap map;
    map["CanSeek"] = _player.canSeek();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoPreviousChanged()
{
    LOG_TRACE(_logger, "onCanGoPreviousChanged()");
    QVariantMap map;
    map["CanGoPrevious"] = _player.canGoPrevious();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoNextChanged()
{
    LOG_TRACE(_logger, "onCanGoNextChanged()");
    QVariantMap map;
    map["CanGoNext"] = _player.canGoNext();
    signalPlayerUpdate(map);
}

void Mpris2Player::onVolumeChanged()
{
    LOG_TRACE(_logger, "onVolumeChanged()");
    QVariantMap map;
    map["Volume"] = _player.volume();
    signalPlayerUpdate(map);
}

QMap<QString, QVariant> Mpris2Player::toXesam(const Song& song)
{
    LOG_TRACE(_logger, "toXesam('" + song.toString() + "')");
    QMap<QString, QVariant> map;
    if (song.isValid())
    {
        QStringList artist;
        artist.append(song.artist());
        map["xesam:url"] = song.title();
        map["xesam:artist"] = artist;
        map["xesam:album"] = song.album();
        map["xesam:title"] = song.title();
        map["xesam:userRating"] = song.isFavorite() ? 1 : 0;
        if (song.duration())
            map["mpris:length"] = (qlonglong) song.duration() * SEC_TO_MICROSEC;
        else
            map["mpris:length"] = 1;
        QString trackId = QString("/org/mpris/MediaPlayer2/MellowPlayer/Track/%1").arg(song.uniqueId());
        map["mpris:trackid"] = QVariant(QDBusObjectPath(trackId).path());
        auto url = _localAlbumArt.url();
        if (url.startsWith("file://"))
            map["mpris:artUrl"] = url;
        else
            map["mpris:artUrl"] = "file://" + _localAlbumArt.url();
    }
    else
    {
        QStringList artist;
        artist.append("");
        map["xesam:url"] = "";
        map["xesam:artist"] = artist;
        map["xesam:album"] = "";
        map["xesam:title"] = "";
        map["mpris:length"] = 0;
        map["mpris:trackid"] = QVariant(QDBusObjectPath("/org/mpris/MediaPlayer2/NoTrack").path());
        map["mpris:artUrl"] = "";
        map["xesam:userRating"] = 0;
    }
    LOG_TRACE(_logger, "metadata: {" + qMapToString(map) + "\n}");
    return map;
}

QString Mpris2Player::statusToString(PlaybackStatus status)
{
    // a player that is buffering is considered to be paused for mpris, otherwise
    // the player disappear on Plasma 5.
    if (status == PlaybackStatus::Buffering)
        status = PlaybackStatus::Paused;
    switch (status)
    {
    case PlaybackStatus::Playing:
        return "Playing";
    case PlaybackStatus::Paused:
        return "Paused";
    default:
        return "Stopped";
    }
}

void Mpris2Player::signalPlayerUpdate(const QVariantMap& map)
{
    LOG_TRACE(_logger, "signalPlayerUpdate");
    signalUpdate(map, "org.mpris.MediaPlayer2.Player");
}

void Mpris2Player::signalUpdate(const QVariantMap& map, const QString& interfaceName)
{
    LOG_TRACE(_logger, "signalUpdate");
    QVariantMap mapWithOrigin = map;
    mapWithOrigin["origin"] = "MellowPlayer";
    if (!mapWithOrigin.isEmpty())
    {
        QDBusMessage signal = QDBusMessage::createSignal("/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", "PropertiesChanged");
        QVariantList args = QVariantList() << interfaceName << mapWithOrigin << QStringList();
        signal.setArguments(args);

        LOG_TRACE(_logger, "PropertiesChanged: {" + qMapToString(mapWithOrigin) + "\n}");
        QDBusConnection::sessionBus().send(signal);
    }
}

QString Mpris2Player::qMapToString(const QMap<QString, QVariant>& map)
{
    QString output;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        // Format output here.
        output += QString("\n\t%1=%2,").arg(it.key()).arg(it.value().toString());
    }
    return output;
}
