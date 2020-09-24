#include <MellowPlayer/Infrastructure/Network/HttpClient.hpp>
#include <QNetworkReply>

using namespace MellowPlayer::Infrastructure;

HttpClient::HttpClient()
{
    connect(&_networkAccessManager, &QNetworkAccessManager::finished, this, &HttpClient::onFinished);
}

void HttpClient::get(const QUrl& url)
{
    _networkAccessManager.get(QNetworkRequest(url));
}

void HttpClient::onFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
        qWarning() << "http request failed: " << reply->errorString();

    auto replyData = reply->readAll();
    if (_callback)
        _callback(replyData);
    emit replyReceived(replyData);
}

void HttpClient::get(const QUrl& url, const std::function<void(const QByteArray& replyData)>& callback)
{
    _callback = callback;
    get(url);
}
