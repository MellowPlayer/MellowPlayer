#pragma once

#include <QObject>
#include <QtDBus>

namespace MellowPlayer::Domain
{
    class Song;
    class IPlayer;
    class ILocalAlbumArt;
    class ILogger;

    enum class PlaybackStatus;
}

namespace MellowPlayer::Presentation
{
    class Mpris2Player : public QDBusAbstractAdaptor
    {
        Q_OBJECT
        Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
    public:
        explicit Mpris2Player(Domain::IPlayer& player, Domain::ILocalAlbumArt& localAlbumArt, QObject* parent = nullptr);

        Q_PROPERTY(QVariantMap Metadata READ metadata)
        Q_PROPERTY(bool CanControl READ canControl)
        Q_PROPERTY(bool CanSeek READ canSeek)
        Q_PROPERTY(bool CanPause READ canPause)
        Q_PROPERTY(bool CanPlay READ canPlay)
        Q_PROPERTY(bool CanStope READ canStop)
        Q_PROPERTY(bool CanGoPrevious READ canGoPrevious)
        Q_PROPERTY(bool CanGoNext READ canGoNext)
        Q_PROPERTY(qlonglong Position READ position)
        Q_PROPERTY(int MinimuRate READ minimumRate)
        Q_PROPERTY(int MaximuRate READ maximumRate)
        Q_PROPERTY(double Rate READ rate WRITE setRate)
        Q_PROPERTY(double Volume READ volume WRITE setVolume)
        Q_PROPERTY(bool Shuffle READ shuffle WRITE setShuffle)
        Q_PROPERTY(QString LoopStatus READ loopStatus WRITE setLoopStatus)
        Q_PROPERTY(QString PlaybackStatus READ playbackStatus)

        QString playbackStatus();
        QString loopStatus();
        void setLoopStatus(const QString& status);
        bool shuffle();
        void setShuffle(bool value);
        double volume();
        void setVolume(double value);
        QVariantMap metadata();
        double minimumRate();
        double maximumRate();
        double rate();
        void setRate(float value);
        qlonglong position();
        bool canGoNext();
        bool canGoPrevious();
        bool canPlay();
        bool canStop();
        bool canPause();
        bool canSeek();
        bool canControl();

    public slots:
        void PlayPause();
        void Play();
        void Pause();
        void Stop();
        void Next();
        void Previous();
        void Seek(qlonglong position);
        void SetPosition(const QDBusObjectPath& trackId, qlonglong position);

    signals:
        void Seeked(qlonglong);

    private slots:
        void onPlaybackStatusChanged();
        void onSongChanged(Domain::Song* song);
        void onFavoriteChanged();
        void onArtUrlChanged();
        void onPositionChanged();
        void onDurationChanged();
        void onCanSeekChanged();
        void onCanGoPreviousChanged();
        void onCanGoNextChanged();
        void onVolumeChanged();

    private:
        QMap<QString, QVariant> toXesam(const Domain::Song& song);
        QString statusToString(Domain::PlaybackStatus status);
        void signalPlayerUpdate(const QVariantMap& map);
        void signalUpdate(const QVariantMap& map, const QString& interfaceName);

        QString qMapToString(const QMap<QString, QVariant>& map);

        static const qlonglong SEC_TO_MICROSEC;
        static const qlonglong SEEK_DELTA_LIMIT;

        qlonglong _previousPosition;
        Domain::ILogger& _logger;
        Domain::IPlayer& _player;
        Domain::ILocalAlbumArt& _localAlbumArt;
        QMap<QString, QVariant> _currentSongMetadata;
    };
}
