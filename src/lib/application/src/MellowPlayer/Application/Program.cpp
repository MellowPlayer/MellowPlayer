#define BOOST_DI_CFG_DIAGNOSTICS_LEVEL 2

void logStart();
#include "Program.hpp"
#include <MellowPlayer/Application/DiConfig.hpp>
#include <MellowPlayer/Application/Initialization/InitializationSequence.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/CommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Presentation/HiDPISupport.h>
#include <QApplication>
#include <QTimer>
#include <QtQuickControls2/QQuickStyle>
#include <QtWebEngine>
#include <boost/di.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
namespace di = boost::di;

Program::Program(InitializationSequence& initializationSequence, IApplication& application)
        : _logger(Loggers::logger("Program")), _initializationSequence(initializationSequence), _application(application)
{
}

int Program::execute()
{
    initialize();
    auto returnCode = _application.run();
    cleanUp();
    return returnCode;
}

void Program::initialize() const
{
    LOG_DEBUG(_logger, "Initializing application");

    _initializationSequence.initialize([=](bool success) {
        if (success)
        {
            LOG_DEBUG(_logger, "Initialization finished with success");
        }
        else
        {
            LOG_ERROR(_logger, "Initialization finished with failure");
            QTimer::singleShot(1, [=]() { _application.quit(-1); });
        }
    });
}

void Program::cleanUp() const
{
    _initializationSequence.cleanUp();
}

//**************************************************************************************************************************************************************
void configureEnvironment()
{
    qputenv("QTWEBENGINE_DIALOG_SET", "QtQuickControls2");
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "4242");

    QCoreApplication::setApplicationName("MellowPlayer3");
    QCoreApplication::setApplicationVersion(BuildConfig::getVersion());
    QCoreApplication::setOrganizationDomain("com.gitlab.ColinDuquesnoy");
    QCoreApplication::setOrganizationName("MellowPlayer");
}

void configureHiDpiSupport()
{
    HiDPISupport hiDPISupport;
    hiDPISupport.configure();
}

void configureLogging()
{
    LoggerConfig loggerConfig;
    if (SingleInstanceCheckup::IsAnotherInstanceRunning())
        loggerConfig.logFilePrefix = "Secondary.";
    auto loggerFactory = std::make_shared<SpdLoggerFactory>();
    Loggers::initialize(loggerFactory, loggerConfig);
}

void logStart()
{
    auto& logger = Loggers::logger("main");
    auto logDirectory = FileHelper::logDirectory();
    auto version = BuildConfig::getVersion();
    auto buildInfo = BuildConfig::buildInfo();

    LOG_WARN(logger, "****************************** Starting ***************************************");
    LOG_INFO(logger, QString("MellowPlayer %1 - %2").arg(version).arg(buildInfo));
    LOG_INFO(logger, "Log directory: " + logDirectory);
}

void logStop()
{
    auto& logger = Loggers::logger("main");
    auto logDirectory = FileHelper::logDirectory();
    auto version = BuildConfig::getVersion();
    auto buildInfo = BuildConfig::buildInfo();

    LOG_WARN(logger, "****************************** Stopped ***************************************");
}

void configureForQmlAndWebEngine(QApplication& qApplication)
{
    qApplication.setApplicationDisplayName("MellowPlayer");
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    // With Qt < 5.14 it is recommended to initialize qtwebengine AFTER creating QApplication
    QtWebEngine::initialize();
#endif
    QQuickStyle::setStyle("Material");
}

int Program::main(int argc, char** argv)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    // With Qt >= 5.14 it is recommended to initialize qtwebengine BEFORE creating QApplication
    QtWebEngine::initialize();
#endif

    configureEnvironment();
    configureHiDpiSupport();
    configureLogging();

    QApplication qApplication(argc, argv);
    configureForQmlAndWebEngine(qApplication);

    CommandLineArguments commandLineArguments;
    commandLineArguments.parse();

    Loggers::instance().setDefaultLogLevel(commandLineArguments.logLevel());
    logStart();

    di::extension::detail::scoped scope{};
    auto injector = defaultInjector(scope, qApplication, commandLineArguments);

    auto program = injector.create<Program&>();
    auto returnCode = program.execute();
    logStop();
    return returnCode;
}
