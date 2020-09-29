#include "Fakes/FakeQmlApplicationEngine.hpp"
#include "Fakes/FakeQmlSingleton.hpp"
#include <Fakes/FakePlayer.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingletons.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("QmlSingletonsTests")
{
    GIVEN("A QmlSingletons instance with a fake qml application engine and one property")
    {
        FakeQmlApplicationEngine qmlApplicationEngine;
        FakePlayer player;
        auto qmlSingleton = std::make_shared<FakeQmlSingleton>("Foo");
        QmlSingletons qmlSingletons(qmlApplicationEngine, player, {qmlSingleton});

        WHEN("I call initialize")
        {
            qmlSingletons.registerToQml();

            THEN("player name exists in qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty("CurrentPlayer"));
            }

            AND_THEN("the correct player property object has been added to qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.qmlSingleton("CurrentPlayer") == &player);
            }

            AND_THEN("property name exists in qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.hasContextProperty(qmlSingleton->name()));
            }

            AND_THEN("the correct property object has been added to qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.qmlSingleton(qmlSingleton->name()) == qmlSingleton.get());
            }
        }
    }
}
