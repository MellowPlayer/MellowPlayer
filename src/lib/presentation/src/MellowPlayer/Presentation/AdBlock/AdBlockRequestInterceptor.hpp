#pragma once

#include <QWebEngineUrlRequestInterceptor>

namespace MellowPlayer::Domain
{
    class ILogger;
    class Settings;
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class AdBlockRequestInterceptor : public QWebEngineUrlRequestInterceptor
    {
    public:
        AdBlockRequestInterceptor(Domain::Settings& settings);

        void interceptRequest(QWebEngineUrlRequestInfo &info) override;

    private:
        static QString blackList[];

        Domain::ILogger& _logger;
        Domain::Setting& _isAdBlockEnabled;
    };
}

