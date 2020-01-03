#pragma once

#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>

namespace MellowPlayer::Domain
{
    class IApplicationStatusFile;
    class Settings;
    class ILogger;

    class RemoteControl : public IRemoteControl
    {
    public:
        RemoteControl(IApplicationStatusFile& applicationStatusFile, Settings& settings, IRemoteControlApplication& remoteControlApplication);

        bool isEnabled() const override;
        void setEnabled(bool value) override;
        void activate() override;
        void deactivate() override;

        bool isAutoStartEnabled() const override;
        void setAutoStartEnabled(bool value) override;

        IRemoteControlApplication& application() const override;

    private:
        ILogger& _logger;
        IApplicationStatusFile& _applicationStatusFile;
        Settings& _settings;
        IRemoteControlApplication& _remoteControlApplication;
    };
}
