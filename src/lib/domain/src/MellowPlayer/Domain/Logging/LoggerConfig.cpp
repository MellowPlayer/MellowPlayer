#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

string LoggerConfig::DEFAULT_LOG_FORMAT = "[%L] [%P] [%Y-%m-%d %H-%M-%S:%f] [%n] %v";

LoggerConfig::LoggerConfig() : LoggerConfig(LogLevel::Debug)
{
}

LoggerConfig::LoggerConfig(LogLevel level)
{
    logLevel = level;
    logFormat = DEFAULT_LOG_FORMAT;
    showFileAndLine = true;
    logFilePrefix = "";
}
