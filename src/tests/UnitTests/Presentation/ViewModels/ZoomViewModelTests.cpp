#include <Fakes/FakeQmlSingletons.hpp>
#include <Fakes/FakeSettingsStore.hpp>
#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ZoomViewModel tests")
{
    FakeSettingsStore settingsStore;
    ZoomViewModel sut(settingsStore);

    double defaultValue = 1;

    WHEN("zoom has not been changed")
    {
        THEN("default value is correct")
        {
            REQUIRE(sut.value() == defaultValue);
        }
    }

    WHEN("zoom value is changed")
    {
        double newValue = 2.0;
        sut.setValue(newValue);

        THEN("new value is returned")
        {
            REQUIRE(sut.value() == newValue);

            AND_THEN("new value is stored in settings store")
            {
                REQUIRE(settingsStore.value("zoom") == newValue);
            }
        }

        AND_WHEN("reset is called")
        {
            sut.reset();
            THEN("value is reset to default value")
            {
                REQUIRE(sut.value() == defaultValue);

                AND_THEN("default value is stored in settings store")
                {
                    REQUIRE(settingsStore.value("zoom") == defaultValue);
                }
            }
        }
    }

    WHEN("zoom is incremented")
    {
        auto previousValue = sut.value();
        sut.increment();

        THEN("value is higher")
        {
            REQUIRE(sut.value() > previousValue);

            AND_THEN("new value is stored in settings store")
            {
                REQUIRE(settingsStore.value("zoom") == sut.value());
            }
        }
    }

    WHEN("zoom is decremented")
    {
        auto previousValue = sut.value();
        sut.decrement();

        THEN("value is lower")
        {
            REQUIRE(sut.value() < previousValue);

            AND_THEN("new value is stored in settings store")
            {
                REQUIRE(settingsStore.value("zoom") == sut.value());
            }
        }
    }
}