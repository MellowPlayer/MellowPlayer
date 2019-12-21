#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/CommandLineArguments.hpp>
#include <QDebug>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

CommandLineArguments::CommandLineArguments()
        : _serviceOption(QStringList() << "s"
                                       << "service",
                         "Select startup service",
                         "service"),
          _logLevelOption(QStringList() << "l"
                                        << "log-level",
                          "Log level (0=TRACE, 1=DEBUG, 2=INFO, 3=WARNING, 4=ERROR, 5=CRITICAL, 6=OFF)",
                          "logLevel",
                          "1"),
          _playPauseOption(QStringList() << "p"
                                         << "play-pause",
                           "Play or pause the current song"),
          _nextOption(QStringList() << "f"
                                    << "next",
                      "Skip to the next song"),
          _previousOption(QStringList() << "b"
                                        << "previous",
                          "Skip to the previous song"),
          _toggleFavoriteOption(QStringList() << "t"
                                              << "toggle-favorite-song",
                                "Add or remove the current song to/from your favorites"),
          _autoQuitDelayOption(QStringList() << "d"
                                             << "auto-quit-delay",
                               "Auto quit delay [ms]",
                               "autoQuitDelay"),
          _startMinimizedOption(QStringList() << "m"
                                              << "start-minimized",
                                "Starts the application in minimized state")
{
}

void CommandLineArguments::parse()
{
    _parser.setApplicationDescription("Cloud music player for your desktop!");
    _parser.addVersionOption();
    _parser.addHelpOption();
    _parser.addOption(_serviceOption);
    _parser.addOption(_logLevelOption);
    _parser.addOption(_playPauseOption);
    _parser.addOption(_nextOption);
    _parser.addOption(_previousOption);
    _parser.addOption(_toggleFavoriteOption);
    _parser.addOption(_autoQuitDelayOption);
    _parser.addOption(_startMinimizedOption);

    QStringList webEngineOptions = QStringList() << "--remote-debugging-port"
                                                 << "--ppapi-flash-path"
                                                 << "--ppapi-flash-version"
                                                 << "--ppapi-widevine-path"
                                                 << "--register-pepper-plugins"
                                                 << "--touch-events";
    QStringList args;
    for (auto arg : qApp->arguments())
    {
        bool addArg = true;
        for (auto webEngineOption : webEngineOptions)
        {
            if (arg.startsWith(webEngineOption))
            {
                addArg = false;
                break;
            }
        }
        if (addArg)
            args << arg;
    }
    _parser.process(args);

    _service = _parser.value(_serviceOption);
    int logLevelValue = _parser.value(_logLevelOption).toInt();
    if (logLevelValue < 0 || logLevelValue > static_cast<int>(LogLevel::Off))
        _logLevel = LogLevel::Info;
    else
        _logLevel = static_cast<LogLevel>(logLevelValue);
    _autoQuitDelay = _parser.value(_autoQuitDelayOption).toInt();

    _playRequested = _parser.isSet(_playPauseOption);
    _previousRequested = _parser.isSet(_previousOption);
    _nextRequested = _parser.isSet(_nextOption);
    _toggleFavoriteRequested = _parser.isSet(_toggleFavoriteOption);
    _startMinimized = _parser.isSet(_startMinimizedOption);
}

QString CommandLineArguments::service() const
{
    return _service;
}

int CommandLineArguments::autoQuitDelay() const
{
    return _autoQuitDelay;
}

bool CommandLineArguments::playPauseRequested() const
{
    return _playRequested;
}

bool CommandLineArguments::nextRequested() const
{
    return _nextRequested;
}

bool CommandLineArguments::previousRequested() const
{
    return _previousRequested;
}

LogLevel CommandLineArguments::logLevel() const
{
    return _logLevel;
}
bool CommandLineArguments::toggleFavoriteRequested() const
{
    return _toggleFavoriteRequested;
}

bool CommandLineArguments::startMinimized() const
{
    return _startMinimized;
}