#pragma once

#include <QObject>

namespace MellowPlayer::Domain
{
    class IRemoteControlApplication;

    class IRemoteControl : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IRemoteControl() = default;

        virtual bool isEnabled() const = 0;
        virtual void setEnabled(bool value) = 0;

        virtual void activate() = 0;
        virtual void deactivate() = 0;

        virtual bool isAutoStartEnabled() const = 0;
        virtual void setAutoStartEnabled(bool value) = 0;

        virtual IRemoteControlApplication& application() const = 0;

    signals:
        void enabledChanged();
        void autoStartEnabledChanged();
    };
}