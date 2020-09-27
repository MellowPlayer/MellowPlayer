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
        QmlSingletons(IQmlApplicationEngine& qmlApplicationEngine, Domain::IPlayer& player, const std::vector<std::shared_ptr<IQmlSingleton>>& items);

        void registerToQml() override;

    private:
        IQmlApplicationEngine& _qmlApplicationEngine;
        Domain::IPlayer& _player;
        std::vector<std::shared_ptr<IQmlSingleton>> _items;
    };
}
