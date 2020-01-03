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
    class RemoteControlCheckup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit RemoteControlCheckup(Domain::IRemoteControl& remoteControl);

        void initialize(const ResultCallback& resultCallback) override;
        bool isEnabled() const override;

        QString errorMessage() const override;

    private:
        Domain::ILogger& _logger;
        Domain::IRemoteControl& _remoteControl;
        Domain::IRemoteControlApplication& _remoteControlApplication;
        QString _errorMessage;
    };
}
