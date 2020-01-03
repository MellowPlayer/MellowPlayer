#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Domain
{
    class IRemoteControl;
}

namespace MellowPlayer::Application
{
    class RemoteControlSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit RemoteControlSetup(Domain::IRemoteControl& remoteControl);

        void initialize(const ResultCallback& resultCallback) override;
        bool isEnabled() const override;

    private:
        Domain::IRemoteControl& _remoteControl;
    };
}
