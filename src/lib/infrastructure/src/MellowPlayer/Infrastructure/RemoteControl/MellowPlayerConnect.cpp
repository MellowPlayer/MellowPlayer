#include "MellowPlayerConnect.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <QtCore/QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

MellowPlayerConnect::MellowPlayerConnect() : _logger(Loggers::logger("MellowPlayerConnect")), _minimumRequiredVersion(0, 2, 0)
{
}

QString MellowPlayerConnect::logo() const
{
    return "qrc:/MellowPlayer/Infrastructure/images/mellowplayer-connect.svg";
}

QString MellowPlayerConnect::name() const
{
    return "MellowPlayer.Connect";
}

QString MellowPlayerConnect::version() const
{
    return _minimumRequiredVersion.toString();
}

QString MellowPlayerConnect::minimumRequiredVersion() const
{
    return _minimumRequiredVersion.toString();
}

QString MellowPlayerConnect::homePage() const
{
    return "https://gitlab.com/ColinDuquesnoy/mellowplayer-connect";
}

QString MellowPlayerConnect::url() const
{
    for (auto& address : QNetworkInterface::allAddresses())
    {
        if(!address.isLoopback() && address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            auto url = "http://" + address.toString() + ":5000";
            return url;
        }
    }
    return "";
}

InstallationState MellowPlayerConnect::checkInstallation()
{
    return InstallationState::UpToDate;
}

InstallationState MellowPlayerConnect::installationState() const
{
    return _installationState;
}

void MellowPlayerConnect::install(const IRemoteControlApplication::InstallCallback& installCallback)
{
    LOG_DEBUG(_logger, "Installing " << name());
    stop();
    setInstalling(true);

    QTimer::singleShot(5000, [=]() {
        setInstallationState(checkInstallation());
        // execute process and call below lines in callback
        setInstalling(false);
        installCallback(true, "");
    });
}

bool MellowPlayerConnect::isInstalling() const
{
    return _installing;
}

void MellowPlayerConnect::start()
{
    LOG_DEBUG(_logger, "Starting " << name());
    setRunning(true);
}

void MellowPlayerConnect::stop()
{
    LOG_DEBUG(_logger, "Stopping " << name());
    setRunning(false);
}

bool MellowPlayerConnect::isRunning() const
{
    return _running;
}

void MellowPlayerConnect::setInstallationState(InstallationState value)
{
    if (_installationState != value)
    {
        _installationState = value;
        emit installationStateChanged();
    }
}
void MellowPlayerConnect::setRunning(bool value)
{
    if (_running != value)
    {
        _running = value;
        emit runningChanged();
    }
}
void MellowPlayerConnect::setInstalling(bool value)
{
    if (_installing != value)
    {
        _installing = value;
        emit installingChanged();
    }
}
