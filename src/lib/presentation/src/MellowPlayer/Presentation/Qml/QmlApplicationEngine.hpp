#pragma once

#include "IQmlApplicationEngine.hpp"
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

        void setContextProperty(const QString& name, QObject* object) override;
        void setContextProperty(const QString& name, const QVariant& value) override;
        void addImportPath(const QString& path) override;
        bool load(const QUrl& url) override;
        void reset() override;

    private:
        std::shared_ptr<QQmlApplicationEngine> _engine;
    };
}
