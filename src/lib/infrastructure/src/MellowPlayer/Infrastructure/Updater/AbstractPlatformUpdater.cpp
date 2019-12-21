#include <MellowPlayer/Infrastructure/Network/IFileDownloader.hpp>
#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <QTemporaryDir>

using namespace MellowPlayer::Infrastructure;

AbstractPlatformUpdater::AbstractPlatformUpdater(IFileDownloader& fileDownloader) : _fileDownloader(fileDownloader)
{
    connect(&fileDownloader, &IFileDownloader::progressChanged, this, &AbstractPlatformUpdater::progressUpdated);
    connect(&fileDownloader, &IFileDownloader::finished, this, &AbstractPlatformUpdater::downloadFinished);
}

void AbstractPlatformUpdater::setRelease(const Release* release)
{
    _release = release;
}

void AbstractPlatformUpdater::download()
{
    if (_release)
    {
        _assetFilePath = makeDestinationPath();
        _fileDownloader.download(assetUrl(), _assetFilePath);
    }
}

QString AbstractPlatformUpdater::makeDestinationPath()
{
    QString tempDir = QTemporaryDir().path();
    QDir().mkpath(tempDir);
    return tempDir + "/" + assetFileName();
}

void AbstractPlatformUpdater::install()
{
    emit progressUpdated(-1);
    doInstall(_assetFilePath);
}
