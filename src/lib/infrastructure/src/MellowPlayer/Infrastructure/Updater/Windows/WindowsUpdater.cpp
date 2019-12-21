#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <MellowPlayer/Infrastructure/Updater/Windows/WindowsUpdater.hpp>
#include <QApplication>
#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>

using namespace MellowPlayer::Infrastructure;

WindowsUpdater::WindowsUpdater(IFileDownloader& fileDownloader) : AbstractPlatformUpdater(fileDownloader)
{
}

bool WindowsUpdater::canInstall() const
{
    return _asset.isValid() && _asset.isWindowsInstaller();
}

void WindowsUpdater::doInstall(const QString& assetLocalPath)
{
    _installerPath = assetLocalPath;
    // no installation here, we'll start the installer when user clicked on restart
    emit installFinished(QFile::exists(_installerPath));
}

QString WindowsUpdater::assetUrl() const
{
    return _asset.url();
}

QString WindowsUpdater::assetFileName() const
{
    return _asset.name();
}

void WindowsUpdater::setRelease(const Release* release)
{
    AbstractPlatformUpdater::setRelease(release);

    if (_release != nullptr)
    {
        for (auto& asset : _release->assets())
        {
            if (asset.isWindowsInstaller())
            {
                _asset = asset;
                break;
            }
        }
    }
}

void WindowsUpdater::restart()
{
    QProcess::startDetached(_installerPath);
    qApp->quit();
}
