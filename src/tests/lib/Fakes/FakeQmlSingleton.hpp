#pragma once

#include <MellowPlayer/Presentation/Qml/IQmlSingleton.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeQmlSingleton : public QObject, public IQmlSingleton
    {
    public:
        void registerTo(IQmlApplicationEngine& qmlApplicationEngine) override
        {
            qmlApplicationEngine.registerSingletonInstance(name, propertyObject);
        }

        QString name;
        QObject* propertyObject = nullptr;
    };
}
