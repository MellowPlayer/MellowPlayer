#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLogger.hpp>
#include <QDebug>
#include <iostream>

using namespace std;
using namespace spdlog;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

shared_ptr<spdlog::sinks::rotating_file_sink_mt> SpdLogger::_errorSink = nullptr;
shared_ptr<spdlog::sinks::rotating_file_sink_mt> SpdLogger::_allSink = nullptr;

shared_ptr<logger> SpdLogger::createLogger(const string& name, const LoggerConfig& config)
{
    try
    {
        // configure sinks
        vector<sink_ptr> sinks;
        if (config.createConsoleLogger && details::os::in_terminal(stdout))
        {
#ifdef Q_OS_WIN
            sinks.push_back(make_shared<sinks::stdout_sink_mt>());
#else
            sinks.push_back(make_shared<sinks::ansicolor_stdout_sink_mt>());
#endif
        }

        if (config.createFileLoggers)
        {
            auto logDir = FileHelper::createLogDirectory().toStdString();
            auto logFileName = logDir + name;

            if (SpdLogger::_errorSink == nullptr)
            {
                SpdLogger::_errorSink = make_shared<sinks::rotating_file_sink_mt>(logDir + "Errors.log", 1024 * 1024 * 20, 5);
                SpdLogger::_errorSink->set_level(level::warn);
            }
            sinks.push_back(SpdLogger::_errorSink);

            if (SpdLogger::_allSink == nullptr)
            {
                SpdLogger::_allSink = make_shared<sinks::rotating_file_sink_mt>(logDir + "All.log", 1024 * 1024 * 20, 5);
            }
            sinks.push_back(SpdLogger::_allSink);
        }

        // create and register logger
        auto combined_logger = make_shared<logger>(name, begin(sinks), end(sinks));
        combined_logger->set_pattern(config.logFormat);
        combined_logger->set_level(static_cast<level::level_enum>(config.logLevel));
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
    if (SpdLogger::_allSink)
    {
        SpdLogger::_allSink->set_level(spdLogLevel);
    }
    _logger->set_level(spdLogLevel);
}
