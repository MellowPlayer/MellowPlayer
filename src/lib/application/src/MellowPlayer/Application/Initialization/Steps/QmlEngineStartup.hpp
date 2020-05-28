#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;
}

namespace MellowPlayer::Application
{
    class QmlEngineStartup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit QmlEngineStartup(Presentation::IQmlApplicationEngine& qmlApplicationEngine);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

    private:
        Presentation::IQmlApplicationEngine& _qmlApplicationEngine;
    };
}
