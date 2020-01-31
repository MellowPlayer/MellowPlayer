#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <QQmlContext>

using namespace MellowPlayer::Presentation;

void QmlApplicationEngine::setContextProperty(const QString& name, QObject* object)
{
    _engine.rootContext()->setContextProperty(name, object);
}

void QmlApplicationEngine::addImportPath(const QString& path)
{
    _engine.addImportPath(path);
}

bool QmlApplicationEngine::load(const QUrl& url)
{
    _engine.load(url);
    return _engine.rootObjects().count() > 0;
}

void QmlApplicationEngine::setContextProperty(const QString& name, const QVariant& value)
{
    _engine.rootContext()->setContextProperty(name, value);
}
