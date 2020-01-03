#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/ILoggerFactory.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <QtCore/QLoggingCategory>

using namespace MellowPlayer::Domain;
using namespace std;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    string category(context.category != nullptr ? context.category : "qt");
    ILogger& logger = Loggers::logger(category == "default" ? "qt" : category);

    // QtCriticalMsg, QtFatalMsg, QtSystemMsg = QtCriticalMsg
    std::map<int, LogLevel> toLogLevel = {{QtDebugMsg, LogLevel::Debug},
                                          {QtInfoMsg, LogLevel::Info},
                                          {QtWarningMsg, LogLevel::Warning},
                                          {QtCriticalMsg, LogLevel::Error},
                                          {QtFatalMsg, LogLevel::Critical}};
    auto logLevel = toLogLevel[type];

    if (category == "js" || message.startsWith("Remote debugging"))
        logLevel = LogLevel::Debug;

    if (message.startsWith("Attribute Qt::AA_ShareOpenGLContexts must be set"))
        logLevel = LogLevel::Trace;

    logger.log(message.toStdString(), logLevel, context.file, context.line);
}

unique_ptr<Loggers> Loggers::_instance = nullptr;

Loggers& Loggers::initialize(std::shared_ptr<ILoggerFactory> loggerFactory, const LoggerConfig& defaultConfig)
{
    _instance.reset(new Loggers(loggerFactory, defaultConfig));
    return *_instance;
}

Loggers& Loggers::initialize(std::shared_ptr<ILoggerFactory> loggerFactory, LogLevel logLevel)
{
    auto& loggingManager = initialize(loggerFactory);
    loggingManager.setDefaultLogLevel(logLevel);
    return loggingManager;
}

Loggers& Loggers::instance()
{
    if (_instance == nullptr)
        throw logic_error("Loggers::instance called before Loggers::initialize!");
    return *_instance;
}

Loggers::Loggers(std::shared_ptr<ILoggerFactory> loggerFactory, const LoggerConfig& defaultConfig)
        : _loggerFactory(loggerFactory), _defaultLoggerConfig(defaultConfig)
{
    qInstallMessageHandler(messageHandler);
}

ILogger& Loggers::logger()
{
    return logger("root");
}

ILogger& Loggers::logger(const std::string& name)
{
    return logger(name, instance()._defaultLoggerConfig);
}

ILogger& Loggers::logger(const std::string& name, const LoggerConfig& loggerConfig)
{
    if (instance().loggerExists(name))
        return instance().getExistingLogger(name);
    else
        return instance().createNewLogger(name, loggerConfig);
}

bool Loggers::loggerExists(const std::string& name)
{
    return _loggersMap.find(name) != _loggersMap.end();
}

ILogger& Loggers::getExistingLogger(const std::string& name)
{
    return *_loggersMap[name];
}

ILogger& Loggers::createNewLogger(const std::string& name, const LoggerConfig& loggerConfig)
{
    _loggersMap[name] = _loggerFactory->create(name, loggerConfig);
    return getExistingLogger(name);
}

void Loggers::setDefaultLogLevel(LogLevel logLevel)
{
    _defaultLoggerConfig.logLevel = logLevel;

    for (auto logger : _loggersMap)
    {
        logger->setLogLevel(logLevel);
    }
}
