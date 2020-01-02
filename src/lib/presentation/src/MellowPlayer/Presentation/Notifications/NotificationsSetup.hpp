#pragma once

#include "NotificationFactory.hpp"
#include <MellowPlayer/Domain/IInitializable.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class INotificationPresenter;
    class IPlayerNotifications;

    class NotificationsSetup : public Domain::IInitializable
    {
        Q_OBJECT
    public:
        NotificationsSetup(IPlayerNotifications& playerNotifications, INotificationPresenter& presenter);

        void initialize(const ResultCallback& resultCallback) override;
        QString toString() const override;

    private:
        IPlayerNotifications& _playerNotifications;
        INotificationPresenter& _notificationsPresenter;
    };
}
