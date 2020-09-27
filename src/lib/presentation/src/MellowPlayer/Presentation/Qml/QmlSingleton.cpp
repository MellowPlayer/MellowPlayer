#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingletons.hpp>

using namespace MellowPlayer::Presentation;

QmlSingleton::QmlSingleton(const QString& name, QObject* instance)
        : _name(name), _instance(instance)
{
}

void QmlSingleton::registerTo(IQmlApplicationEngine& qmlApplicationEngine)
{
    qmlApplicationEngine.registerSingletonInstance(_name, _instance);
}

QObject* QmlSingleton::instance()
{
    return _instance;
}
