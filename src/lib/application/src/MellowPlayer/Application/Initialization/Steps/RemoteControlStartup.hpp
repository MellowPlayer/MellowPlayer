#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Domain
{
    class IRemoteControl;
    class IRemoteControlApplication;
    class ILogger;
}

namespace MellowPlayer::Application
{
    class RemoteControlStartup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit RemoteControlStartup(Domain::IRemoteControl& remoteControl);

        void initialize(const ResultCallback& resultCallback) override;
        bool isEnabled() const override;

    private:
        Domain::ILogger& _logger;
        Domain::IRemoteControl& _remoteControl;
        Domain::IRemoteControlApplication& _remoteControlApplication;
    };
}
