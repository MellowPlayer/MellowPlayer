#include <Fakes/FakeQmlApplicationEngine.hpp>
#include <Fakes/FakeQmlSingletons.hpp>
#include <Fakes/FakeSettingsStore.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("MainWindowViewModelTests")
{
    GIVEN("A main window instance")
    {
        auto qmlSingletons = std::make_shared<FakeQmlSingletons>();
        FakeSettingsStore settingsStore;
        MainWindowViewModel mainWindow(*qmlSingletons, settingsStore);

        WHEN("Creating main window")
        {
            THEN("it is added to the qml singleton")
            {
                qmlSingletons->contains(mainWindow);
            }

            AND_THEN("window is not yet visible")
            {
                REQUIRE(!mainWindow.isVisible());
            }
        }

        WHEN("showing the window")
        {
            QSignalSpy spy(&mainWindow, &MainWindowViewModel::visibleChanged);

            mainWindow.show();

            THEN("window is visible")
            {
                REQUIRE(mainWindow.isVisible());
            }

            AND_THEN("visibleChanged has been emitted")
            {
                REQUIRE(spy.count() == 1);
            }

            AND_WHEN("hiding the window")
            {
                mainWindow.hide();

                THEN("window is not visible anymore")
                {
                    REQUIRE(!mainWindow.isVisible());
                }

                AND_THEN("visibleChanged has been emitted once again")
                {
                    REQUIRE(spy.count() == 2);
                }
            }
        }

        WHEN("I call requestQuit")
        {
            QSignalSpy spy(&mainWindow, &MainWindowViewModel::quitRequest);
            mainWindow.requestQuit();

            THEN("quitRequest signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }
    }
}
