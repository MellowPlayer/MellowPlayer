#include "MellowPlayerConnect.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

MellowPlayerConnect::MellowPlayerConnect() : _logger(Loggers::logger("MellowPlayerConnect")), _minimumRequiredVersion(0, 2, 0)
{
}

QString MellowPlayerConnect::logo() const
{
    return "";
}

QString MellowPlayerConnect::name() const
{
    return "MellowPlayer.Connect";
}

QString MellowPlayerConnect::version() const
{
    return _minimumRequiredVersion.toString();
}

InstallationState MellowPlayerConnect::installationState() const
{
    return InstallationState::NotInstalled;
}

void MellowPlayerConnect::install(const IRemoteControlApplication::InstallCallback& installCallback)
{
    LOG_INFO(_logger, "Installing " << name());
    checkInstallation();
    installCallback(false, "Not implemented");
}

bool MellowPlayerConnect::isInstalling() const
{
    return false;
}

void MellowPlayerConnect::start()
{
    LOG_INFO(_logger, "Starting " << name());
}

void MellowPlayerConnect::stop()
{
    LOG_INFO(_logger, "Stopping " << name());
}

InstallationState MellowPlayerConnect::checkInstallation()
{
    return installationState();
}
