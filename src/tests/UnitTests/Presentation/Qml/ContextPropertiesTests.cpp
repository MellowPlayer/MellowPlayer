#include "FakeContextProperty.hpp"
#include "FakeQmlApplicationEngine.hpp"
#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <Mocks/PlayerMock.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ContextPropertiesTests")
{
    GIVEN("A context properties instance with a fake qml application engine and one property")
    {
        FakeQmlApplicationEngine qmlApplicationEngine;
        auto playerMock = PlayerMock::get();
        ContextProperties contextProperties(qmlApplicationEngine, playerMock.get());
        FakeContextProperty contextProperty;
        contextProperty.name = "foo";
        contextProperty.propertyObject = &contextProperty;
        contextProperties.add(contextProperty);

        WHEN("I call initialize")
        {
            contextProperties.registerToQml();

            THEN("player name exists in qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty("_player"));
            }

            AND_THEN("the correct player property object has been added to qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.contextProperty("_player") == &playerMock.get());
            }

            AND_THEN("property name exists in qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty(contextProperty.name));
            }

            AND_THEN("the correct property object has been added to qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.contextProperty(contextProperty.name) == &contextProperty);
            }
        }
    }
}
