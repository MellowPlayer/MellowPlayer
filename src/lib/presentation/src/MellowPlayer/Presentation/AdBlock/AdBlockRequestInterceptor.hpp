#pragma once

#include <QWebEngineUrlRequestInterceptor>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Presentation
{
    class AdBlockRequestInterceptor : public QWebEngineUrlRequestInterceptor
    {
    public:
        AdBlockRequestInterceptor();

        void interceptRequest(QWebEngineUrlRequestInfo &info) override;

    private:
        static QString blackList[];

        Domain::ILogger& _logger;
    };
}

