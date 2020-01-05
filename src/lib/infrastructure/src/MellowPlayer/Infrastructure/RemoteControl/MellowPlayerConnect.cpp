#include "MellowPlayerConnect.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Infrastructure/System/ITextFile.hpp>
#include <MellowPlayer/Infrastructure/System/ITextFileFactory.hpp>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

MellowPlayerConnect::MellowPlayerConnect(ITextFileFactory& textFileFactory)
        : _textFileFactory(textFileFactory),
          _logger(Loggers::logger("MellowPlayer.Connect")),
          _minimumRequiredVersion(0, 2, 0),
          _installationDirectory(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first() + QDir::separator() + "RemoteControl" +
                                 QDir::separator() + "mellowplayer-connect")
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
    return _version.toString();
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
        if (!address.isLoopback() && address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            auto url = "http://" + address.toString() + ":5000";
            return url;
        }
    }
    return "";
}

InstallationState MellowPlayerConnect::checkInstallation()
{
    LOG_DEBUG(_logger, "Installation directory: " << _installationDirectory);
    auto versionPath = _installationDirectory + QDir::separator() + "version";
    auto versionFile = _textFileFactory.create(versionPath);
    if (!versionFile->exists())
    {
        LOG_DEBUG(_logger, versionPath << " not found -> NotInstalled");
        setInstallationState(InstallationState::NotInstalled);
    }
    else
    {
        _version = QVersionNumber::fromString(versionFile->read().split(QRegExp("[\r\n]"), QString::SkipEmptyParts).first());
        bool upToDate = _version >= _minimumRequiredVersion;
        LOG_DEBUG(_logger, "Found version " << _version.toString() << ", required version is " << _minimumRequiredVersion.toString() << ": " << (upToDate ? "OK" : "NOK"));
        setInstallationState(upToDate ? InstallationState::UpToDate : InstallationState::Outdated);
    }
    return installationState();
}

InstallationState MellowPlayerConnect::installationState() const
{
    return _installationState;
}

void MellowPlayerConnect::install(const IRemoteControlApplication::InstallCallback& installCallback)
{
    if (isRunning())
        stop();

    LOG_DEBUG(_logger, "Installing " << name());
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
    // TODO pay attention to use the same process, what about flatpak?
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
