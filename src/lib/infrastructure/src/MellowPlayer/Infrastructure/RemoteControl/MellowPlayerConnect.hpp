#pragma once

#include <MellowPlayer/Domain/RemoteControl/IRemoteControlApplication.hpp>
#include <QtCore/QVersionNumber>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class MellowPlayerConnect : public Domain::IRemoteControlApplication
    {
    public:
        MellowPlayerConnect();

        QString logo() const override;
        QString name() const override;
        QString version() const override;

        Domain::InstallationState checkInstallation() override;

        Domain::InstallationState installationState() const override;
        void install(const InstallCallback& installCallback) override;
        bool isInstalling() const override;

        void start() override;
        void stop() override;

    private:
        Domain::ILogger& _logger;
        QVersionNumber _minimumRequiredVersion;
    };
}