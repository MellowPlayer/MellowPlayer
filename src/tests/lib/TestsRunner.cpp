#include "TestsRunner.hpp"
#define CATCH_CONFIG_RUNNER
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <QDebug>
#include <QSettings>
#include <QtWebEngine/qtwebengineglobal.h>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

int TestsRunner::runTests(int argc, char** argv)
{
    Q_INIT_RESOURCE(infrastructure);
    Q_INIT_RESOURCE(presentation);

    QtWebEngine::initialize();

    QApplication application(argc, argv);
    application.setApplicationName("MellowPlayer.Tests");
    application.setApplicationDisplayName("MellowPlayer.Tests");
    application.setOrganizationName("MellowPlayer.Tests");
    application.setOrganizationDomain("org.mellowplayer.tests");

    auto loggerFactory = std::make_shared<SpdLoggerFactory>();
    LoggerConfig loggerConfig;

    try
    {
        Loggers::instance();
        assert(false);
    }
    catch (const logic_error&)
    {
    }
    Loggers& loggingManager = Loggers::initialize(loggerFactory, loggerConfig);
    loggingManager.setDefaultLogLevel(LogLevel::Error);

    LOG_DEBUG(loggingManager.logger("tests"), "Starting tests");
    qDebug() << "Starting tests" << BuildConfig::buildInfo();

    QSettings settings;
    settings.clear();
    auto retCode = Catch::Session().run(argc, argv);

    settings.clear();

    return retCode;
}
