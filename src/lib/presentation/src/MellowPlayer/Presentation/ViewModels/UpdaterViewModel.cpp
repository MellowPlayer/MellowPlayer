#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

UpdaterViewModel::UpdaterViewModel(Updater& updater, std::shared_ptr<IContextProperties> contextProperties)
        : ContextProperty("_updater", this, contextProperties), _updater(updater)
{
    connect(&updater, &Updater::updateAvailable, this, &UpdaterViewModel::onUpdateAvailable);
    connect(&updater, &Updater::noUpdateAvailable, this, &UpdaterViewModel::onNoUpdateAvailable);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::statusChanged);
    connect(&updater, &Updater::statusChanged, this, &UpdaterViewModel::busyChanged);
    connect(&updater, &Updater::progressUpdated, this, &UpdaterViewModel::onProgressUpdated);
    connect(&updater, &Updater::installed, this, &UpdaterViewModel::onInstalled);
    emit statusChanged();
    emit busyChanged();
}

bool UpdaterViewModel::visible() const
{
    return _visible;
}

bool UpdaterViewModel::installEnabled() const
{
    return _installEnabled;
}

double UpdaterViewModel::progress() const
{
    return _progress;
}

void UpdaterViewModel::close()
{
    setVisible(false);
}

void UpdaterViewModel::check()
{
    setProgress(-1);
    _updater.check();
}

void UpdaterViewModel::install()
{
    setInstallEnabled(false);
    setRestartEnabled(false);
    setProgress(-1);
    _updater.install();
}

void UpdaterViewModel::restart()
{
    setInstallEnabled(false);
    setRestartEnabled(false);
    setProgress(-1);
    setVisible(false);
    _updater.restart();
}

void UpdaterViewModel::setVisible(bool visible)
{
    if (_visible == visible)
        return;

    _visible = visible;
    emit visibleChanged();
}

void UpdaterViewModel::setInstallEnabled(bool enabled)
{
    if (_installEnabled == enabled)
        return;

    _installEnabled = enabled;
    emit installEnabledChanged();
}

void UpdaterViewModel::setProgress(double progress)
{
    if (_progress == progress)
        return;

    _progress = progress;
    emit progressChanged();
}

void UpdaterViewModel::onUpdateAvailable()
{
    setInstallEnabled(_updater.canInstall());
    setRestartEnabled(false);
    setProgress(-1);
    setVisible(true);
}

void UpdaterViewModel::onNoUpdateAvailable()
{
    setInstallEnabled(false);
    setRestartEnabled(false);
    setProgress(-1);
    setVisible(false);
}

QString UpdaterViewModel::url() const
{
    const Release* r = _updater.latestRelease();
    if (r != nullptr)
        return r->url();
    return "";
}

QString UpdaterViewModel::status() const
{
    return UpdaterStatusConverter().toString(_updater.status());
}

bool UpdaterViewModel::busy() const
{
    return _updater.status() == Updater::Status::Checking || _updater.status() == Updater::Status::Downloading ||
           _updater.status() == Updater::Status::Installing;
}

void UpdaterViewModel::onProgressUpdated(double progress)
{
    setProgress(progress);
}
bool UpdaterViewModel::restartEnabled() const
{
    return _restartEnabled;
}
void UpdaterViewModel::setRestartEnabled(bool enabled)
{
    if (_restartEnabled != enabled)
    {
        _restartEnabled = enabled;
        emit restartEnabledChanged();
    }
}
void UpdaterViewModel::onInstalled()
{
    setInstallEnabled(false);
    setRestartEnabled(true);
}
