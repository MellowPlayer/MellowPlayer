#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

using namespace MellowPlayer::Presentation;

ContextProperty::ContextProperty(const QString& name, QObject* propertyObject, std::shared_ptr<IContextProperties> contextProperties)
        : name_(name), propertyObject_(propertyObject)
{
    contextProperties->add(*this);
}

void ContextProperty::initialize(IQmlApplicationEngine& qmlApplicationEngine)
{
    qmlApplicationEngine.setContextProperty(name_, propertyObject_);
}
