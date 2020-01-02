#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QDebug>

using namespace MellowPlayer::Presentation;

ContextProperty::ContextProperty(const QString& name, QObject* propertyObject, IContextProperties& contextProperties)
        : _name(name), _propertyObject(propertyObject)
{
    contextProperties.add(*this);
}

void ContextProperty::registerTo(IQmlApplicationEngine& qmlApplicationEngine)
{
    qDebug() << "Registering context property " << _name << ":" << _propertyObject->metaObject()->className();
    qmlApplicationEngine.setContextProperty(_name, _propertyObject);
}
