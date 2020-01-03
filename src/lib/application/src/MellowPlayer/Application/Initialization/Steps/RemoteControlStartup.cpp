#include "RemoteControlStartup.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>
#include <MellowPlayer/Domain/RemoteControl/IRemoteControlApplication.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Application;

RemoteControlStartup::RemoteControlStartup(IRemoteControl& remoteControl)
        : _logger(Loggers::logger("RemoteControlStartup")), _remoteControl(remoteControl), _remoteControlApplication(remoteControl.application())
{
}

void RemoteControlStartup::initialize(const ResultCallback& resultCallback)
{
    if (_remoteControl.isAutoStartEnabled())
    {
        if (!_remoteControlApplication.isInstalled())
        {
            LOG_WARN(_logger, "Cannot start " << _remoteControlApplication.name() << ", application is not installed");
        }
        else
        {
            if (_remoteControlApplication.isOutdated())
                LOG_WARN(_logger, "Outdated version of " << _remoteControlApplication.name() << " will be started");

            LOG_INFO(_logger, "Starting up " << _remoteControlApplication.name());
            _remoteControlApplication.start();
        }
    }
    else
    {
        LOG_DEBUG(_logger, "Automatic start-up disabled, doing nothing");
    }

    resultCallback(true);
}
