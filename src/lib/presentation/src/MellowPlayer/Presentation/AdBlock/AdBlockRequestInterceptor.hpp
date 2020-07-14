#pragma once

#include <QWebEngineUrlRequestInterceptor>
#include <QSet>

namespace MellowPlayer::Domain
{
    class ILogger;
    class Settings;
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class IAdBlockRequestInterceptor : public QWebEngineUrlRequestInterceptor
    {
    public:
        virtual ~IAdBlockRequestInterceptor() = default;

        virtual void block(QString hostname) = 0;
    };

    class AdBlockRequestInterceptor : public IAdBlockRequestInterceptor
    {
    public:
        explicit AdBlockRequestInterceptor(Domain::Settings& settings);

        void interceptRequest(QWebEngineUrlRequestInfo &info) override;
        void block(QString hostname) override;

    private:
        Domain::ILogger& _logger;
        Domain::Setting& _isAdBlockEnabled;
        QSet<QString> _blocklist;

        bool isBlocked(QString hostname) const;
    };
}

