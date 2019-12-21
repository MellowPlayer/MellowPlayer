#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/ILatestRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

Updater::Updater(ILatestRelease& releaseQuerier, Settings& settings, AbstractPlatformUpdater& platformUpdater)
        : _logger(Loggers::logger("Updater")),
          _releaseQuerier(releaseQuerier),
          _platformUpdater(platformUpdater),
          _autoCheckEnabledSetting(settings.get(SettingKey::MAIN_CHECK_FOR_UPDATES)),
          _updateChannelSetting(settings.get(SettingKey::MAIN_UPDATE_CHANNEL)),
          _currentRelease(&Release::current())
{
    releaseQuerier.setChannel(getChannel());
    connect(&releaseQuerier, &ILatestRelease::received, this, &Updater::onLatestReleaseReceived);
    connect(&_updateChannelSetting, &Setting::valueChanged, this, &Updater::check);
    connect(&platformUpdater, &AbstractPlatformUpdater::progressUpdated, this, &Updater::progressUpdated);
    connect(&platformUpdater, &AbstractPlatformUpdater::downloadFinished, this, &Updater::onDownloadFinished);
    connect(&platformUpdater, &AbstractPlatformUpdater::installFinished, this, &Updater::onInstallFinished);
}

void Updater::check()
{
    LOG_INFO(_logger, "Checking for update");
    setStatus(Status::Checking);
    _releaseQuerier.setChannel(getChannel());
    _releaseQuerier.get();
}

UpdateChannel Updater::getChannel() const
{
    return static_cast<UpdateChannel>(_updateChannelSetting.value().toInt());
}

void Updater::install()
{
    LOG_INFO(_logger, "Downloading update");
    setStatus(Status::Downloading);
    _platformUpdater.download();
}

bool Updater::isUpdateAvailable() const
{
    return _isUpdateAvailable;
}

bool Updater::canInstall() const
{
    return _platformUpdater.canInstall();
}

const Release* Updater::latestRelease() const
{
    return _latestRelease;
}

void Updater::onLatestReleaseReceived(const Release* release)
{
    if (release != nullptr && *release > *_currentRelease)
    {
        LOG_INFO(_logger, QString("Latest release is an update (%1 < %2)").arg(_currentRelease->name()).arg(release->name()));
        setStatus(Status::UpdateAvailable);
        _latestRelease = release;
        _platformUpdater.setRelease(_latestRelease);
        _isUpdateAvailable = true;
        emit updateAvailable();
    }
    else
    {
        LOG_INFO(_logger, QString("Current release is up to date..."));
        setStatus(Status::None);
        _latestRelease = nullptr;
        _isUpdateAvailable = false;
        emit noUpdateAvailable();
    }
}

void Updater::setCurrentRelease(const Release* currentRelease)
{
    _currentRelease = currentRelease;
}

Updater::Status Updater::status() const
{
    return _status;
}

void Updater::setStatus(Updater::Status status)
{
    if (_status != status)
    {
        _status = status;
        emit statusChanged();
    }
}

void Updater::onDownloadFinished(bool succes)
{
    if (succes)
    {
        LOG_INFO(_logger, "download finished, installing...")
        setStatus(Status::Installing);
        _platformUpdater.install();
    }
    else
    {
        LOG_ERROR(_logger, "download failed")
        setStatus(Status::Failure);
    }
}
void Updater::onInstallFinished(bool succes)
{
    if (succes)
    {
        LOG_INFO(_logger, "install finished, you can now restart the application");
        setStatus(Status::Installed);
        emit installed();
    }
    else
    {
        LOG_ERROR(_logger, "install failed");
        setStatus(Status::Failure);
    }
}
void Updater::restart()
{
    _platformUpdater.restart();
}
