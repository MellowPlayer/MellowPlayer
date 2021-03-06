#pragma once

#include <QString>

namespace MellowPlayer::Domain
{
    enum class LogLevel;
}

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments
    {
    public:
        virtual ~ICommandLineArguments() = default;
        virtual void parse() = 0;
        virtual QString service() const = 0;
        virtual int autoQuitDelay() const = 0;
        virtual bool playPauseRequested() const = 0;
        virtual bool nextRequested() const = 0;
        virtual bool previousRequested() const = 0;
        virtual bool toggleFavoriteRequested() const = 0;
        virtual Domain::LogLevel logLevel() const = 0;
        virtual bool startMinimized() const = 0;
        virtual bool allowMultipleInstances() const = 0;
    };
}
