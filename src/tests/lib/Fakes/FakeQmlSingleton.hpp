#pragma once

#include <MellowPlayer/Presentation/Qml/IQmlSingleton.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeQmlSingleton : public QObject, public IQmlSingleton
    {
    public:
        FakeQmlSingleton(const QString& name) : _name(name)
        {

        }

        QString name() const { return _name; }

        void registerTo(IQmlApplicationEngine& qmlApplicationEngine) override
        {
            qmlApplicationEngine.registerSingletonInstance(_name, this);
        }

    private:
        QString _name;
    };
}
