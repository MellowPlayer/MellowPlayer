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

void QmlApplicationEngine::load(const QUrl& url)
{
    _engine.load(url);
}
