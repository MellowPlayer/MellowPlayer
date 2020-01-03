#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Domain
{
    class IRemoteControlApplication;
    class ILogger;
}

namespace MellowPlayer::Application
{
    class RemoteControlCheckup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit RemoteControlCheckup(Domain::IRemoteControlApplication& remoteControl);

        void initialize(const ResultCallback& resultCallback) override;

        QString errorMessage() const override;

    private:
        Domain::ILogger& _logger;
        Domain::IRemoteControlApplication& _remoteControlApplication;
        QString _errorMessage;
    };
}
