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

        static std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> _errorSink;
        static std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> _allSink;
    };
}
