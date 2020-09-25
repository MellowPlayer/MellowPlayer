#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class IStreamingServicesViewModel;
}

namespace MellowPlayer::Application
{
    class StreamingServicesSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit StreamingServicesSetup(Presentation::IStreamingServicesViewModel& streamingServices);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::IStreamingServicesViewModel& _streamingServices;
    };
}
