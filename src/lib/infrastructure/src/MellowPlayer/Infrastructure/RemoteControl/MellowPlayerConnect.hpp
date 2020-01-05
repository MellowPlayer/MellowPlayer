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
        QString minimumRequiredVersion() const override;
        QString homePage() const override;
        QString url() const override;

        Domain::InstallationState checkInstallation() override;

        Domain::InstallationState installationState() const override;
        void install(const InstallCallback& installCallback) override;
        bool isInstalling() const override;

        void start() override;
        void stop() override;
        bool isRunning() const override;

    private:
        void setInstallationState(Domain::InstallationState value);
        void setRunning(bool value);
        void setInstalling(bool value);

        bool _running = false;
        bool _installing = false;
        Domain::InstallationState _installationState = Domain::InstallationState::NotInstalled;
        Domain::ILogger& _logger;
        QVersionNumber _minimumRequiredVersion;
    };
}