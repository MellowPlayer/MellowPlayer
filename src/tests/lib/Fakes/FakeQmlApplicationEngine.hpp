#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QUrl>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeQmlApplicationEngine : public IQmlApplicationEngine
    {
    public:
        void registerSingletonInstance(const QString& name, QObject* object) override
        {
            _qmlSingletons[name] = object;
        }

        bool hasContextProperty(const QString& name)
        {
            return _qmlSingletons.contains(name);
        }

        QObject* qmlSingleton(const QString& name) const
        {
            return _qmlSingletons[name];
        }

        void addImportPath(const QString& path) override
        {
            _importPaths.append(path);
        }

        int importPathsCount()
        {
            return _importPaths.count();
        }

        bool load(const QUrl& url) override
        {
            _loadedUrl = url;
            return true;
        }

        bool isLoaded() const
        {
            return !_loadedUrl.isEmpty();
        }

        void reset() override
        {

        }

    private:
        QMap<QString, QObject*> _qmlSingletons;
        QStringList _importPaths;
        QUrl _loadedUrl;
    };
}
