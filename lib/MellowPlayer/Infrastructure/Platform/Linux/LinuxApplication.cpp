#include <MellowPlayer/Application/IQtApplication.hpp>
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "LinuxApplication.hpp"

#ifdef Q_OS_LINUX

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

LinuxApplication::LinuxApplication(IQtApplication& qtApp,
                                   IMainWindow& mainWindow,
                                   StreamingServicesController& streamingServices,
                                   IHotkeysController& kotkeys,
                                   ISystemTrayIcon& systemTrayIcon,
                                   INotifier& notifier,
                                   IMprisController& mprisService) :
        CoreApplication(qtApp, mainWindow, streamingServices, kotkeys, systemTrayIcon, notifier),
        logger(LoggingManager::instance().getLogger("LinuxApplication")),
        mprisService(mprisService) {

}

void LinuxApplication::initialize() {
    LOG_TRACE(logger, "initialize");
    CoreApplication::initialize();
    mprisService.start();
}

#endif