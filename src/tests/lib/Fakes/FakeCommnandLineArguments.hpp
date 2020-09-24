#pragma once

#include <memory>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeCommandLineArguments : public ICommandLineArguments
    {
    public:
        void parse() override
        {
            parsed = true;
        }

        void setService(const QString& service)
        {
            _service = service;
        }

        QString service() const override
        {
            return _service;
        }

        int autoQuitDelay() const override
        {
            return 0;
        }

        bool playPauseRequested() const override
        {
            return _playPauseRequested;
        }

        void setPlayPauseRequested(bool value)
        {
            _playPauseRequested = value;
        }

        bool nextRequested() const override
        {
            return _nextRequested;
        }

        void setNextRequested(bool value)
        {
            _nextRequested = value;
        }

        bool previousRequested() const override
        {
            return _previousRequested;
        }

        void setPreviousRequested(bool value)
        {
            _previousRequested = value;
        }

        bool toggleFavoriteRequested() const override
        {
            return _toggleFavoriteRequested;
        }

        void setToggleFavoriteRequested(bool value)
        {
            _toggleFavoriteRequested = value;
        }

        Domain::LogLevel logLevel() const override
        {
            return Domain::LogLevel::Error;
        }

        bool startMinimized() const override
        {
            return false;
        }

        bool allowMultipleInstances() const override
        {
            return false;
        }

        bool parsed = false;

    private:
        QString _service;
        bool _playPauseRequested = false;
        bool _nextRequested = false;
        bool _previousRequested = false;
        bool _toggleFavoriteRequested = false;
    };
}
