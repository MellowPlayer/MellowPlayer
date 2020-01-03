#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <memory>
#include <spdlog/spdlog.h>

namespace MellowPlayer::Infrastructure
{
    class SpdLogger : public Domain::ILogger
    {
    public:
        SpdLogger(const std::string& name, const Domain::LoggerConfig& config);

        void log(const std::string& message, Domain::LogLevel level, const char* file, int line) override;
        const std::string& name() const override;

        void setLogLevel(Domain::LogLevel level) override;

    private:
        static std::shared_ptr<spdlog::logger> createLogger(const std::string& name, const Domain::LoggerConfig& config);

        std::shared_ptr<spdlog::logger> _logger;
        bool _includeFileAndLine;
        std::string _name;

        static spdlog::sink_ptr _consoleSink;
        static spdlog::sink_ptr _errorFileSink;
        static spdlog::sink_ptr _allFileSink;
    };
}
