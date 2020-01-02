#pragma once

#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <QList>
#include <QMap>
#include <QMutex>

namespace MellowPlayer::Domain
{
    class Song;
    class IListeningHistoryDatabase;
    class ILogger;
    class IPlayer;
    class Setting;
    class Settings;

    class IListeningHistory : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IListeningHistory() = default;

        virtual void load() = 0;
        virtual QList<Domain::ListeningHistoryEntry> toList() const = 0;
        virtual int count() const = 0;
        virtual void clear() = 0;
        virtual void removeById(int entryId) = 0;
        virtual void removeByService(const QString& serviceName) = 0;
        virtual void removeManyById(const QList<int>& ids) = 0;

    public slots:
        virtual void addSong(Domain::Song* song) = 0;

    signals:
        void entryAdded(const Domain::ListeningHistoryEntry& entry);
        void entryRemoved(int entryId);
        void entriesCleared();
    };

    class ListeningHistory : public IListeningHistory
    {
        Q_OBJECT
    public:
        ListeningHistory(IListeningHistoryDatabase& model, IPlayer& player_, Settings& settings);

        void load() override;
        QList<Domain::ListeningHistoryEntry> toList() const override;
        int count() const override;
        void clear() override;
        void removeById(int entryId) override;
        void removeByService(const QString& serviceName) override;
        void removeManyById(const QList<int>& ids) override;

    public slots:
        void addSong(Domain::Song* song) override;

    private slots:
        void onPlaybackStatusChanged();
        void onSongChanged(Song* song);
        void onIsEnabledChanged();
        void clearOutdatedEntries();

    private:
        void addSong(const Domain::Song* song, Domain::ListeningHistoryEntry& newEntry);
        void updateRemovedEntries();

        QMap<QString, Domain::ListeningHistoryEntry> _previousEntryPerPlayer;
        QList<Domain::ListeningHistoryEntry> _entries;
        Setting& _isEnabledSetting;
        Setting& _limitSetting;

    protected:
        ILogger& _logger;
        IListeningHistoryDatabase& _database;
        IPlayer& _player;
    };
}
