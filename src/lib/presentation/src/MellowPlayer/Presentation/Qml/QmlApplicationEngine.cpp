#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <QQmlContext>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

QmlApplicationEngine::QmlApplicationEngine()
        : _engine(std::make_shared<QQmlApplicationEngine>()), _logger(Loggers::logger("QmlApplicationEngine"))
{
}

void QmlApplicationEngine::registerSingletonInstance(const QString& name, QObject* object)
{
    LOG_DEBUG(_logger, "Registering singleton: " << name << ":" << object->metaObject()->className());
    qmlRegisterSingletonInstance("MellowPlayer", 3, 0, name.toStdString().c_str(), object);
}

void QmlApplicationEngine::addImportPath(const QString& path)
{
    LOG_DEBUG(_logger, "Adding import path: " << path);
    _engine->addImportPath(path);
}

bool QmlApplicationEngine::load(const QUrl& url)
{
    LOG_DEBUG(_logger, "Loading document: " << url.toString());
    _engine->load(url);
    return _engine->rootObjects().count() > 0;
}

void QmlApplicationEngine::reset()
{
    _engine = nullptr;
}
