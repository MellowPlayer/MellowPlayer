#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <QDir>
#include <QStandardPaths>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

AlbumArtDownloader::AlbumArtDownloader() : _logger(Loggers::logger("AlbumArtDownloader"))
{
    connect(&_fileDownloader, &FileDownloader::finished, this, &AlbumArtDownloader::onDownloadFinished);
}

bool AlbumArtDownloader::download(const QString& url, const QString& songId)
{
    if (url.isEmpty() || songId.isEmpty())
        return false;

    _localUrl = localArtUrl(songId);

    if (_localUrl.exists())
    {
        LOG_DEBUG(_logger, "album art already exists locally")
        emit downloadFinished(_localUrl.absoluteFilePath());
        return true;
    }

    if (isBase64Image(url))
        return createBase64Image(url);

    downloadImage(url);
    return true;
}

void AlbumArtDownloader::downloadImage(const QString& url)
{
    LOG_DEBUG(_logger, "downloading " + url + " to " + _localUrl.absoluteFilePath());
    _fileDownloader.download(url, _localUrl.absoluteFilePath());
}

QFileInfo AlbumArtDownloader::localArtUrl(const QString& songId)
{
    auto cacheDir = QDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    auto dir = QFileInfo(cacheDir, "Covers");
    auto dirPath = dir.absoluteFilePath();
    QDir(cacheDir).mkpath("Covers");
    QFileInfo localArtUrl = QFileInfo(dirPath, songId);
    return localArtUrl;
}

void AlbumArtDownloader::onDownloadFinished(bool success)
{
    LOG_DEBUG(_logger, "download finished");
    if (success)
        emit downloadFinished(_localUrl.absoluteFilePath());
    else
        emit downloadFailed();
}

bool AlbumArtDownloader::isBase64Image(const QString& artUrl)
{
    return _base64Helper.isBase64(artUrl);
}

bool AlbumArtDownloader::createBase64Image(const QString base64String)
{
    LOG_DEBUG(_logger, "creating base64 image from " + base64String + " to " + _localUrl.absoluteFilePath());
    bool retVal = _base64Helper.saveToFile(base64String, _localUrl.absoluteFilePath());
    if (retVal)
        emit downloadFinished(_localUrl.absoluteFilePath());
    return retVal;
}
