#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

string LoggerConfig::DEFAULT_LOG_FORMAT = "[%L] [%P] [%Y-%m-%d %H-%M-%S:%f] [%n] %v";

LoggerConfig::LoggerConfig(LogLevel level)
{
    logLevel = level;
    logFormat = DEFAULT_LOG_FORMAT;
    createConsoleLogger = true;
    createFileLoggers = true;
    showFileAndLine = true;
}

LoggerConfig::LoggerConfig() : LoggerConfig(LogLevel::Debug)
{
}
