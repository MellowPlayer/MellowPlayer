#pragma once

#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <QCommandLineParser>

namespace MellowPlayer::Domain
{
    enum class LogLevel;
}

namespace MellowPlayer::Infrastructure
{
    class CommandLineArguments : public ICommandLineArguments
    {
    public:
        CommandLineArguments();

        void parse() override;

        QString service() const override;
        int autoQuitDelay() const override;
        bool playPauseRequested() const override;
        bool nextRequested() const override;
        bool previousRequested() const override;
        bool toggleFavoriteRequested() const override;
        Domain::LogLevel logLevel() const override;

        bool startMinimized() const override;

    private:
        QCommandLineParser _parser;
        QCommandLineOption _serviceOption;
        QCommandLineOption _logLevelOption;
        QCommandLineOption _playPauseOption;
        QCommandLineOption _nextOption;
        QCommandLineOption _previousOption;
        QCommandLineOption _toggleFavoriteOption;
        QCommandLineOption _autoQuitDelayOption;
        QCommandLineOption _startMinimizedOption;

        QString _service;
        Domain::LogLevel _logLevel;
        bool _playRequested = false;
        bool _nextRequested = false;
        bool _previousRequested = false;
        bool _toggleFavoriteRequested = false;
        int _autoQuitDelay = 0;
        bool _startMinimized = false;
    };
}
