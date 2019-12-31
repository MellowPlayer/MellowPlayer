#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

using namespace MellowPlayer::Presentation;

ContextProperty::ContextProperty(const QString& name, QObject* propertyObject, IContextProperties& contextProperties)
        : _name(name), _propertyObject(propertyObject)
{
    contextProperties.add(*this);
}

void ContextProperty::initialize(IQmlApplicationEngine& qmlApplicationEngine)
{
    qmlApplicationEngine.setContextProperty(_name, _propertyObject);
}
