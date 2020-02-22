#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <QtNetwork/QNetworkAccessManager>

class QNetworkReply;

namespace MellowPlayer::Infrastructure
{
    class HttpClient : public IHttpClient
    {
        Q_OBJECT
    public:
        HttpClient();
        void get(const QUrl& url) override;
        void get(const QUrl& url, const std::function<void(const QByteArray& replyData)>& callback) override;

    private slots:
        void onFinished(QNetworkReply* reply);

    private:
        QNetworkAccessManager _networkAccessManager;
        std::function<void(const QByteArray& replyData)> _callback;
    };
}
