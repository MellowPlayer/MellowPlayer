#pragma once

#include <QObject>
#include <functional>

namespace MellowPlayer::Infrastructure
{
    class IHttpClient : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IHttpClient() = default;
        virtual void get(const QUrl& url) = 0;
        virtual void get(const QUrl& url, const std::function<void(const QByteArray& replyData)>& callback) = 0;

    signals:
        void replyReceived(const QByteArray& replyData);
    };
}