#include "MellowPlayerConnect.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Infrastructure/System/IProcess.hpp>
#include <MellowPlayer/Infrastructure/System/IProcessFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IShellScript.hpp>
#include <MellowPlayer/Infrastructure/System/IShellScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/System/ITextFile.hpp>
#include <MellowPlayer/Infrastructure/System/ITextFileFactory.hpp>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QApplication>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

MellowPlayerConnect::MellowPlayerConnect(ITextFileFactory& textFileFactory, IShellScriptFactory& shellScriptFactory, IProcessFactory& processFactory)
        : _textFileFactory(textFileFactory),
          _shellScriptFactory(shellScriptFactory),
          _processFactory(processFactory),
          _logger(Loggers::logger("MellowPlayer.Connect")),
          _minimumRequiredVersion(0, 2, 3),
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        _version = QVersionNumber::fromString(versionFile->read().split(QRegExp("[\r\n]"), Qt::SkipEmptyParts).first());
#else
        _version = QVersionNumber::fromString(versionFile->read().split(QRegExp("[\r\n]"), QString::SkipEmptyParts).first());
#endif
        bool upToDate = _version >= _minimumRequiredVersion;
        LOG_DEBUG(
                _logger,
                "Found version " << _version.toString() << ", required version is " << _minimumRequiredVersion.toString() << ": " << (upToDate ? "OK" : "NOK"));
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
    if (isInstalling())
        return;

    if (isRunning())
        stop();

    LOG_DEBUG(_logger, "Installing " << name());
    setInstalling(true);

    _installScript = _shellScriptFactory.create();
    QString downloadUrl = QString("https://gitlab.com/ColinDuquesnoy/mellowplayer-connect/-/jobs/artifacts/%1/raw/mellowplayer-connect.%2?job=%3")
                                  .arg(minimumRequiredVersion());
    ;
#if defined(Q_OS_UNIX)
    downloadUrl = downloadUrl.arg("tar.gz").arg("publish-linux-x64");
    _installScript->setScript(":/MellowPlayer/Infrastructure/scripts/install-mellowplayer-connect.sh");
#else
    downloadUrl = downloadUrl.arg("zip").arg("publish-win-x64");
    _installScript->setScript(":/MellowPlayer/Infrastructure/scripts/install-mellowplayer-connect.ps1");
#endif

    _installScript->setScriptArguments({downloadUrl, _installationDirectory});
    _installScript->execute([=](int exitCode, const QString&, const QString& errorOutput) {
        LOG_DEBUG(_logger, "Installion finished");
        setInstallationState(checkInstallation());
        // execute process and call below lines in callback
        setInstalling(false);
        installCallback(exitCode == 0, errorOutput);
    });

    QTimer::singleShot(5000, [=]() {

    });
}

bool MellowPlayerConnect::isInstalling() const
{
    return _installing;
}

void MellowPlayerConnect::start()
{
    LOG_DEBUG(_logger, "Starting " << name());
    _process = _processFactory.create(name());
    auto extension = "";
#ifdef Q_OS_WIN
    extension = ".exe";
#endif

    QStringList arguments {};
    auto executable = QFileInfo(qApp->arguments().first()).canonicalFilePath();
    if (QFileInfo(executable).exists())
    {
        arguments.append("--mellowplayer");
        arguments.append(executable);
    }
    _process->setProgram(_installationDirectory + QDir::separator() + "MellowPlayer.Connect" + extension);
    _process->setArguments(arguments);
    _process->setWorkingDirectory(_installationDirectory);
    _process->execute([=](int, const QString&, const QString&) { LOG_DEBUG(_logger, "Process finished"); });
    setRunning(true);
}

void MellowPlayerConnect::stop()
{
    if (_process == nullptr)
        return;

    LOG_DEBUG(_logger, "Stopping " << name());
    _process->stop();
    _process = nullptr;
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
