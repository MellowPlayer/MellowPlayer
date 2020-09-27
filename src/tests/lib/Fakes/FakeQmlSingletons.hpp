#pragma once

#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlSingleton.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlSingletons.hpp>

namespace MellowPlayer::Presentation::Tests
{
    class FakeQmlSingletons : public IQmlSingletons
    {
    public:
        void setQmlApplicationEngine(IQmlApplicationEngine* qmlApplicationEngine)
        {
            qmlApplicationEngine_ = qmlApplicationEngine;
        }

        bool contains(IQmlSingleton& qmlSingleton)
        {
            return _items.contains(&qmlSingleton);
        }

        void registerToQml() override
        {
            if (qmlApplicationEngine_)
            {
                for (auto* qmlSingleton : _items)
                    if (qmlSingleton)
                        qmlSingleton->registerTo(*qmlApplicationEngine_);
            }
        }

    private:
        QList<IQmlSingleton*> _items;
        IQmlApplicationEngine* qmlApplicationEngine_ = nullptr;
    };

}
