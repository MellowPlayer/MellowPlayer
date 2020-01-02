#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class StreamingServicesViewModel;
}

namespace MellowPlayer::Application
{
    class StreamingServicesSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit StreamingServicesSetup(Presentation::StreamingServicesViewModel& streamingServices);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::StreamingServicesViewModel& _streamingServices;
    };
}
