#pragma once

#include "IContextProperties.hpp"
#include <QList>

namespace MellowPlayer::Domain
{
    class IPlayer;
}

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    /**
     * Implements IContextProperties interface
     */
    class ContextProperties : public IContextProperties
    {
    public:
        /**
         * Ctor
         * @param qmlApplicationEngine Qml application engine used to set context properties.
         */
        ContextProperties(IQmlApplicationEngine& qmlApplicationEngine, Domain::IPlayer& player);

        void add(IContextProperty& contextProperty) override;

        void initialize(const ResultCallback& resultCallback) override;

    private:
        IQmlApplicationEngine& _qmlApplicationEngine;
        QList<IContextProperty*> _contextProperties;
        Domain::IPlayer& _player;
    };
}
