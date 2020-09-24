#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>
#include <UnitTests/Presentation/Qml/FakeQmlApplicationEngine.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("MainWindowViewModelTests")
{
    GIVEN("A main window instance")
    {
        auto contextProperties = std::make_shared<FakeContextProperties>();
        MainWindowViewModel mainWindow(*contextProperties);

        WHEN("Creating main window")
        {
            THEN("it is added to the context properties")
            {
                contextProperties->contains(mainWindow);
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
