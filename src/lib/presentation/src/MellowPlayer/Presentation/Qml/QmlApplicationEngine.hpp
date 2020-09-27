#pragma once

#include "IQmlApplicationEngine.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <QQmlApplicationEngine>
#include <memory>

namespace MellowPlayer::Presentation
{
    /**
     * Implements IQmlApplicationEngine interface
     */
    class QmlApplicationEngine : public IQmlApplicationEngine
    {
    public:
        QmlApplicationEngine();

        void registerSingletonInstance(const QString& name, QObject* object) override;
        void addImportPath(const QString& path) override;
        bool load(const QUrl& url) override;
        void reset() override;

    private:
        std::shared_ptr<QQmlApplicationEngine> _engine;
        Domain::ILogger& _logger;
    };
}
