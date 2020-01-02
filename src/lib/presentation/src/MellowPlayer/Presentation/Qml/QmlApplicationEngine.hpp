#pragma once

#include "IQmlApplicationEngine.hpp"
#include <QtQml/QQmlApplicationEngine>

namespace MellowPlayer::Presentation
{
    /**
     * Implements IQmlApplicationEngine interface
     */
    class QmlApplicationEngine : public IQmlApplicationEngine
    {
    public:
        QmlApplicationEngine() = default;

        void setContextProperty(const QString& name, QObject* object) override;
        void addImportPath(const QString& path) override;
        bool load(const QUrl& url) override;

    private:
        QQmlApplicationEngine _engine;
    };
}
