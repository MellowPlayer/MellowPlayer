#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class INotificationPresenter;
    class IPlayerNotifications;
}

namespace MellowPlayer::Application
{
    class NotificationsSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        NotificationsSetup(Presentation::IPlayerNotifications& playerNotifications, Presentation::INotificationPresenter& presenter);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::IPlayerNotifications& _playerNotifications;
        Presentation::INotificationPresenter& _notificationsPresenter;
    };
}
