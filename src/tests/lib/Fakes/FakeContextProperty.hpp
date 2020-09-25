#pragma once

#include <MellowPlayer/Presentation/Qml/IContextProperty.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeContextProperty : public QObject, public IContextProperty
    {
    public:
        void registerTo(IQmlApplicationEngine& qmlApplicationEngine) override
        {
            qmlApplicationEngine.setContextProperty(name, propertyObject);
        }

        QString name;
        QObject* propertyObject = nullptr;
    };
}
