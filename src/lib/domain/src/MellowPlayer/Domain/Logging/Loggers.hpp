#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <QMap>
#include <memory>
#include <string>

namespace MellowPlayer::Domain
{
    class ILogger;
    class ILoggerFactory;

    class Loggers
    {
    public:
        static Loggers& initialize(std::shared_ptr<ILoggerFactory> loggerFactory, const LoggerConfig& defaultConfig = LoggerConfig());
        static Loggers& initialize(std::shared_ptr<ILoggerFactory> loggerFactory, LogLevel logLevel);
        static Loggers& instance();

        static ILogger& logger();
        static ILogger& logger(const std::string& name);
        static ILogger& logger(const std::string& name, const LoggerConfig& loggerConfig);

        void setDefaultLogLevel(LogLevel logLevel);

    private:
        Loggers(const Loggers& other) = delete;
        Loggers(Loggers&&) = default;
        Loggers& operator=(const Loggers&) = delete;
        Loggers& operator=(Loggers&&) = default;
        Loggers(std::shared_ptr<ILoggerFactory> loggerFactory, const LoggerConfig& defaultConfig);

        bool loggerExists(const std::string& name);
        ILogger& getExistingLogger(const std::string& name);
        ILogger& createNewLogger(const std::string& name, const LoggerConfig& loggerConfig);

        std::shared_ptr<ILoggerFactory> _loggerFactory;
        QMap<std::string, std::shared_ptr<ILogger>> _loggersMap;
        LoggerConfig _defaultLoggerConfig;

        static std::unique_ptr<Loggers> _instance;
    };
}
