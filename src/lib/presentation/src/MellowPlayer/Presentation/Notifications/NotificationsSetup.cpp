#include "NotificationsSetup.hpp"
#include "IPlayerNotifications.hpp"
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

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

QString NotificationsSetup::toString() const
{
    return "Notifications";
}
