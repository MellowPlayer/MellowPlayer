#include "RemoteControlCheckup.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>
#include <MellowPlayer/Domain/RemoteControl/IRemoteControlApplication.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Application;

RemoteControlCheckup::RemoteControlCheckup(IRemoteControl& remoteControl)
        : _logger(Loggers::logger("RemoteControlCheckup")), _remoteControl(remoteControl), _remoteControlApplication(remoteControl.application())
{
}

void RemoteControlCheckup::initialize(const ResultCallback& resultCallback)
{
    switch (_remoteControlApplication.checkInstallation())
    {
    case InstallationState::NotInstalled:
        LOG_WARN(_logger, _remoteControlApplication.name() << " is not installed. Go to \"Settings > Remote Control\" to install it!");
        break;
    case InstallationState::UpToDate:
        LOG_DEBUG(_logger, _remoteControlApplication.name() << " is up to date");
        break;
    case InstallationState::Outdated:
        LOG_DEBUG(_logger, _remoteControlApplication.name() << " is outdated");
        _remoteControlApplication.install([=](bool success, const QString& errorMessage) {
            _errorMessage = "Failed to install " + _remoteControlApplication.name() + ": " + errorMessage;
            resultCallback(success);
        });
        return;
    }

    resultCallback(true);
}

QString RemoteControlCheckup::errorMessage() const
{
    return _errorMessage;
}

bool RemoteControlCheckup::isEnabled() const
{
    return _remoteControl.isEnabled();
}
