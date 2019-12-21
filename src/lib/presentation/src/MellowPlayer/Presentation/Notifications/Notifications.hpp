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

    class INotifications : public Domain::IInitializable
    {
    public:
        virtual bool display(const Notification& notification) = 0;
    };

    class Notifications : public INotifications
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

        Domain::ILogger& logger_;
        Domain::IPlayer& player_;
        Domain::ILocalAlbumArt& localAlbumArt_;
        INotificationPresenter& presenter_;
        Domain::StreamingServices& streamingServices_;
        Domain::Settings& settings_;
        Notification previousNotif_;
        NotificationFactory notificationFactory_;
        QString previousSongId_;
    };
}
