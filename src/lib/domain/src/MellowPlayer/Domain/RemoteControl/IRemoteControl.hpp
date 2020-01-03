#pragma once

namespace MellowPlayer::Domain
{
    class IRemoteControl
    {
    public:
        virtual ~IRemoteControl() = default;

        virtual bool isEnabled() const = 0;
        virtual void setEnabled(bool value) = 0;

        virtual void activate() = 0;
        virtual void deactivate() = 0;

        virtual bool isAutoStartEnabled() const = 0;
        virtual void setAutoStartEnabled(bool value) = 0;
    };
}