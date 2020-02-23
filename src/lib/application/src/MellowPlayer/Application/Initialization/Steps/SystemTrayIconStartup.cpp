#include "SystemTrayIconStartup.hpp"
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

SystemTrayIconStartup::SystemTrayIconStartup(ISystemTrayIcon& systemTrayIcon) : _systemTrayIcon(systemTrayIcon)
{
}

void SystemTrayIconStartup::initialize(const ResultCallback& resultCallback)
{
    _systemTrayIcon.setupFavoritesMenu();
    _systemTrayIcon.show();
    resultCallback(true);
}
