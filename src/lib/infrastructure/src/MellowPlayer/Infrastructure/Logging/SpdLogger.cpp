#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLogger.hpp>
#include <QDebug>
#include <iostream>

using namespace std;
using namespace spdlog;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

sink_ptr SpdLogger::_consoleSink = nullptr;
sink_ptr SpdLogger::_errorFileSink = nullptr;
sink_ptr SpdLogger::_allFileSink = nullptr;

shared_ptr<logger> SpdLogger::createLogger(const string& name, const LoggerConfig& config)
{
    try
    {
        // configure sinks
        vector<sink_ptr> sinks;
        if (details::os::in_terminal(stdout))
        {
            if (SpdLogger::_consoleSink == nullptr)
            {
#ifdef Q_OS_WIN
                SpdLogger::_consoleSink = make_shared<sinks::stdout_sink_mt>();
#else
                SpdLogger::_consoleSink = make_shared<sinks::ansicolor_stdout_sink_mt>();
#endif
                SpdLogger::_consoleSink->set_level(static_cast<level::level_enum>(config.logLevel));
            }
            sinks.push_back(SpdLogger::_consoleSink);
        }

        auto logDir = FileHelper::createLogDirectory().toStdString();
        auto logFileName = logDir + name;

        if (SpdLogger::_errorFileSink == nullptr)
        {
            SpdLogger::_errorFileSink = make_shared<sinks::rotating_file_sink_mt>(logDir + config.logFilePrefix + "Errors.log", 1024 * 1024 * 20, 5);
            SpdLogger::_errorFileSink->set_level(level::warn);
        }
        sinks.push_back(SpdLogger::_errorFileSink);

        if (SpdLogger::_allFileSink == nullptr)
        {
            SpdLogger::_allFileSink = make_shared<sinks::rotating_file_sink_mt>(logDir + config.logFilePrefix + "All.log", 1024 * 1024 * 20, 5);
            SpdLogger::_allFileSink->set_level(level::debug);
        }
        sinks.push_back(SpdLogger::_allFileSink);

        // create and register logger
        auto combined_logger = make_shared<logger>(name, begin(sinks), end(sinks));
        combined_logger->set_pattern(config.logFormat);
        combined_logger->set_level(level::trace);
        register_logger(combined_logger);

        return combined_logger;
    }
    // LCOV_EXCL_START
    catch (const spdlog_ex& ex)
    {
        cout << "SpdLogger (" << name << ") initialization failed: " << ex.what() << endl;
        return nullptr;
    }
    // LCOV_EXCL_STOP
}

SpdLogger::SpdLogger(const string& name, const LoggerConfig& config)
        : _logger(SpdLogger::createLogger(name, config)), _includeFileAndLine(config.showFileAndLine), _name(name)
{
}

void SpdLogger::log(const string& message, LogLevel level, const char* file, int line)
{
    if (_includeFileAndLine && file != nullptr && level == LogLevel::Trace)
        _logger->log(static_cast<level::level_enum>(level), "{} ( \"{}:{}\" )", message, file, line);
    else
        _logger->log(static_cast<level::level_enum>(level), message.c_str());
    _logger->flush();
}

const string& SpdLogger::name() const
{
    return _name;
}

void SpdLogger::setLogLevel(LogLevel level)
{
    auto spdLogLevel = static_cast<level::level_enum>(level);

    if (SpdLogger::_allFileSink && level == LogLevel::Trace)
        SpdLogger::_allFileSink->set_level(spdLogLevel);

    if (SpdLogger::_consoleSink)
        SpdLogger::_consoleSink->set_level(spdLogLevel);
}
