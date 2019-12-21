#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

FileDownloader::FileDownloader() : _logger(Loggers::logger("FileDownloader"))
{
    connect(&_networkAccessManager, &QNetworkAccessManager::finished, this, &FileDownloader::onDownloadFinished);
}

void FileDownloader::download(const QString& urlToDownload, const QString& filePath)
{
    if (!isDownloading())
    {
        LOG_DEBUG(_logger, "downloading " << urlToDownload << " to " << filePath);
        _progress = 0;
        _destinationPath = QFileInfo(filePath);
        _currentReply = _networkAccessManager.get(QNetworkRequest(QUrl(urlToDownload)));
        connect(_currentReply, &QNetworkReply::downloadProgress, this, &FileDownloader::onDownloadProgress);
    }
}

double FileDownloader::progress() const
{
    return _progress;
}

bool FileDownloader::isDownloading() const
{
    return _currentReply != nullptr;
}

void FileDownloader::onDownloadFinished(QNetworkReply* reply)
{
    bool success = false;

    _currentReply = nullptr;

    if (reply->error() == QNetworkReply::NoError)
    {
        QString redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();

        if (!redirectUrl.isEmpty())
        {
            LOG_DEBUG(_logger, "redirected to: " << redirectUrl);
            download(redirectUrl, _destinationPath.absoluteFilePath());
            return;
        }

        QByteArray replyData = reply->readAll();
        QFile file(_destinationPath.absoluteFilePath());
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(replyData);

            LOG_DEBUG(_logger, "file downloaded with success: " << _destinationPath.absoluteFilePath());
            success = true;
        }
        else
            LOG_DEBUG(_logger, "failed to write file: " << _destinationPath.absoluteFilePath() << " - Error: " << file.errorString());
    }
    else
        LOG_DEBUG(_logger, "download failed: " << reply->errorString());

    emit finished(success);
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    double ratio = 0;
    if (bytesTotal > bytesReceived)
        ratio = static_cast<double>(bytesReceived) / bytesTotal;
    double progress = (ratio * 100);

    if (_progress != progress)
    {
        LOG_DEBUG(_logger, "download progress: " << progress);
        _progress = progress;
        emit progressChanged(_progress);
    }
}
