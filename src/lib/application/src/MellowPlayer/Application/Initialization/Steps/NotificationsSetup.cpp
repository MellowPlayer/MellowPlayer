#include "NotificationsSetup.hpp"
#include <MellowPlayer/Presentation/Notifications/IPlayerNotifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

NotificationsSetup::NotificationsSetup(IPlayerNotifications& playerNotifications, INotificationPresenter& presenter)
        : _playerNotifications(playerNotifications), _notificationsPresenter(presenter)
{
}

void NotificationsSetup::initialize(const ResultCallback& resultCallback)
{
    _playerNotifications.listen();
    _notificationsPresenter.initialize();

    resultCallback(true);
}
