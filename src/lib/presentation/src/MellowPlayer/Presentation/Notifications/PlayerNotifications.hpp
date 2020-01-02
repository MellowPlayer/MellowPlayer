#pragma once

#include "IPlayerNotifications.hpp"
#include "NotificationFactory.hpp"
#include <QObject>

namespace MellowPlayer::Domain
{
    class Settings;
    class ILogger;
    class ILocalAlbumArt;
    class IPlayer;
    class StreamingServices;
    class Song;
}

namespace MellowPlayer::Presentation
{
    class INotificationPresenter;

    class PlayerNotifications : public QObject, public IPlayerNotifications
    {
        Q_OBJECT
    public:
        PlayerNotifications(Domain::IPlayer& player,
                            Domain::ILocalAlbumArt& localAlbumArtService,
                            INotificationPresenter& presenter,
                            Domain::StreamingServices& streamingServices,
                            Domain::Settings& settings);

        void listen() override;
        bool display(const Notification& notification) override;

    public slots:
        void onCurrentSongChanged(Domain::Song* song);
        void onPlaybackStatusChanged();

        void onCurrentSongUrlChanged();

    private:
        void showSongNotification(Domain::Song* song, const QString& localAlbumArtUrl);
        bool isPlaying() const;
        const QString currentServiceName() const;
        const QString currentServiceLogo() const;
        bool isNotificationTypeEnabled(NotificationType type) const;

        Domain::ILogger& _logger;
        Domain::IPlayer& _player;
        Domain::ILocalAlbumArt& _localAlbumArt;
        INotificationPresenter& _presenter;
        Domain::StreamingServices& _streamingServices;
        Domain::Settings& _settings;
        Notification _previousNotif;
        NotificationFactory _notificationFactory;
        QString _previousSongId;
    };
}
