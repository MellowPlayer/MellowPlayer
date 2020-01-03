#include "RemoteControlCheckup.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/RemoteControl/IRemoteControlApplication.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Application;

RemoteControlCheckup::RemoteControlCheckup(IRemoteControlApplication& remoteControlApplication)
        : _logger(Loggers::logger("RemoteControlCheckup")), _remoteControlApplication(remoteControlApplication)
{
}

void RemoteControlCheckup::initialize(const ResultCallback& resultCallback)
{
    switch (_remoteControlApplication.checkInstallation())
    {
    case InstallationState::NotInstalled:
        LOG_INFO(_logger, _remoteControlApplication.name() << " is not installed");
        resultCallback(true);
        break;
    case InstallationState::UpToDate:
        LOG_INFO(_logger, _remoteControlApplication.name() << " is up to date");
        resultCallback(true);
        break;
    case InstallationState::Outdated:
        LOG_INFO(_logger, _remoteControlApplication.name() << " is outdated");
        _remoteControlApplication.install([=](bool success, const QString& errorMessage) {
            _errorMessage = "Failed to install " + _remoteControlApplication.name() + ": " + errorMessage;
            resultCallback(success);
        });
        break;
    }
}

QString RemoteControlCheckup::errorMessage() const
{
    return _errorMessage;
}
