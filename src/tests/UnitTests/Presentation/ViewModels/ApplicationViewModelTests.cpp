#include <Fakes/FakeQmlSingletons.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <UnitTests/Infrastructure/Application/FakeApplication.hpp>
#include <UnitTests/Infrastructure/Application/FakeQtApplication.hpp>
#include <UnitTests/Presentation/FakeMainWindow.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

using namespace MellowPlayer::Infrastructure::Tests;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ApplicationViewModelTests")
{
    GIVEN("An applicationViewModel")
    {
        FakeQtApplication qtApplication;
        FakeApplication application;
        FakeMainWindow mainWindow;
        DependencyPool pool;
        SettingsViewModel settingsViewModel(pool.getSettings(), pool.getThemeViewModel());
        ApplicationViewModel applicationViewModel(application, qtApplication, mainWindow, settingsViewModel);

        WHEN("Application is created")
        {
            THEN("windowIcon is set")
            {
                REQUIRE(qtApplication.isIconSet);
            }
        }

        WHEN("commitDataRequest is emitted")
        {
            QSignalSpy spy(&mainWindow, &IMainWindow::forceQuitRequest);

            emit application.commitDataRequest();

            THEN("quitRequest signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("restoreWindow is called")
        {
            application.restoreWindow();

            THEN("mainWindow is shown")
            {
                REQUIRE(mainWindow.isShown);
            }
        }

        WHEN("I call buildInfo")
        {
            QString buildInfoStr = applicationViewModel.buildInfo();

            THEN("buildInfo string is not empty")
            {
                REQUIRE(!buildInfoStr.isEmpty());
            }
        }
    }
}
