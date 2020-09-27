#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingletons.hpp>

using namespace MellowPlayer::Presentation;

QmlSingleton::QmlSingleton(const QString& name, QObject* propertyObject, IQmlSingletons& instance)
        : _name(name), _instance(propertyObject)
{
    instance.add(*this);
}

void QmlSingleton::registerTo(IQmlApplicationEngine& qmlApplicationEngine)
{
    qmlApplicationEngine.registerSingletonInstance(_name, _instance);
}
