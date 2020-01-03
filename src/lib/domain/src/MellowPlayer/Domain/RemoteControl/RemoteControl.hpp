#pragma once

#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>

namespace MellowPlayer::Domain
{
    class IApplicationStatusFile;
    class Settings;

    class RemoteControl : public IRemoteControl
    {
    public:
        RemoteControl(IApplicationStatusFile& applicationStatusFile, Settings& settings);

        bool isEnabled() const override;
        void setEnabled(bool value) override;
        void activate() override;
        void deactivate() override;

        bool isAutoStartEnabled() const override;
        void setAutoStartEnabled(bool value) override;

    private:
        IApplicationStatusFile& _applicationStatusFile;
        Settings& _settings;
    };
}
