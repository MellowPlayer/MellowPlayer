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
          _verboseOption(QStringList() << "V"
                                       << "verbose",
                         "Enable verbose mode"),
          _veryVerboseOption(QStringList() << "W"
                                           << "very-verbose",
                             "Enable very verbose mode"),
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
                                "Starts the application in minimized state"),
          _allowMultipleInstancesOption(QStringList() << "i" << "allow-multiple-instances", "Allow multiple instances of the application")
{
}

void CommandLineArguments::parse()
{
    _parser.setApplicationDescription("Cloud music player for your desktop!");
    _parser.addVersionOption();
    _parser.addHelpOption();
    _parser.addOption(_serviceOption);
    _parser.addOption(_verboseOption);
    _parser.addOption(_veryVerboseOption);
    _parser.addOption(_playPauseOption);
    _parser.addOption(_nextOption);
    _parser.addOption(_previousOption);
    _parser.addOption(_toggleFavoriteOption);
    _parser.addOption(_autoQuitDelayOption);
    _parser.addOption(_startMinimizedOption);
    _parser.addOption(_allowMultipleInstancesOption);

    _parser.process(qApp->arguments());

    _service = _parser.value(_serviceOption);

    _logLevel = LogLevel::Info;
    if (_parser.isSet(_verboseOption))
        _logLevel = LogLevel::Debug;
    if (_parser.isSet(_veryVerboseOption))
        _logLevel = LogLevel::Trace;

    _autoQuitDelay = _parser.value(_autoQuitDelayOption).toInt();

    _playRequested = _parser.isSet(_playPauseOption);
    _previousRequested = _parser.isSet(_previousOption);
    _nextRequested = _parser.isSet(_nextOption);
    _toggleFavoriteRequested = _parser.isSet(_toggleFavoriteOption);
    _startMinimized = _parser.isSet(_startMinimizedOption);
    _allowMultipleInstances = _parser.isSet(_allowMultipleInstancesOption);
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

bool CommandLineArguments::allowMultipleInstances() const
{
    return _allowMultipleInstances;
}
