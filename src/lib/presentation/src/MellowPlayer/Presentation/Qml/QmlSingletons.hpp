#pragma once

#include "IQmlSingletons.hpp"
#include <QList>

namespace MellowPlayer::Domain
{
    class IPlayer;
}

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    /**
     * Implements IQmlSingletons interface
     */
    class QmlSingletons : public IQmlSingletons
    {
    public:
        /**
         * Ctor
         * @param qmlApplicationEngine Qml application engine used to register qml singletons.
         */
        QmlSingletons(IQmlApplicationEngine& qmlApplicationEngine, Domain::IPlayer& player);

        void add(IQmlSingleton& qmlSingleton) override;

        void registerToQml() override;

    private:
        IQmlApplicationEngine& _qmlApplicationEngine;
        QList<IQmlSingleton*> _qmlSingletons;
        Domain::IPlayer& _player;
    };
}
