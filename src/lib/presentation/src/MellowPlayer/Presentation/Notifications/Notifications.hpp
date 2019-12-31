#pragma once

#include "NotificationFactory.hpp"
#include <MellowPlayer/Domain/IInitializable.hpp>
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

    class Notifications : public Domain::IInitializable
    {
        Q_OBJECT
    public:
        Notifications(Domain::IPlayer& player,
                      Domain::ILocalAlbumArt& localAlbumArtService,
                      INotificationPresenter& presenter,
                      Domain::StreamingServices& streamingServices,
                      Domain::Settings& settings);

        void initialize(const ResultCallback& resultCallback) override;
        QString toString() const override;

        bool display(const Notification& notification);

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
