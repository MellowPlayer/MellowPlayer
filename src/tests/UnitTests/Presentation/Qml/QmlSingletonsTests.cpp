#include "Fakes/FakeQmlApplicationEngine.hpp"
#include "Fakes/FakeQmlSingleton.hpp"
#include <Fakes/FakePlayer.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingletons.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ContextPropertiesTests")
{
    GIVEN("A QmlSingletons instance with a fake qml application engine and one property")
    {
        FakeQmlApplicationEngine qmlApplicationEngine;
        FakePlayer player;
        QmlSingletons qmlSingletons(qmlApplicationEngine, player);
        FakeQmlSingleton qmlSingleton;
        qmlSingleton.name = "Foo";
        qmlSingleton.propertyObject = &qmlSingleton;
        qmlSingletons.add(qmlSingleton);

        WHEN("I call initialize")
        {
            qmlSingletons.registerToQml();

            THEN("player name exists in qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty("Player"));
            }

            AND_THEN("the correct player property object has been added to qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.qmlSingleton("Player") == &player);
            }

            AND_THEN("property name exists in qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty(qmlSingleton.name));
            }

            AND_THEN("the correct property object has been added to qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.qmlSingleton(qmlSingleton.name) == &qmlSingleton);
            }
        }
    }
}
