#pragma once

#include <MellowPlayer/Infrastructure/Network/IFileDownloader.hpp>
#include <QFileInfo>
#include <QNetworkAccessManager>

class QNetworkReply;

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class FileDownloader : public IFileDownloader
    {
        Q_OBJECT
    public:
        FileDownloader();

        void download(const QString& urlToDownload, const QString& filePath) override;
        double progress() const override;
        bool isDownloading() const override;

    private slots:
        void onDownloadFinished(QNetworkReply* reply);
        void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    private:
        Domain::ILogger& _logger;
        QNetworkAccessManager _networkAccessManager;
        QFileInfo _destinationPath;
        QNetworkReply* _currentReply = nullptr;
        double _progress = 0;
    };
}
