#include "Fakes/FakeQmlApplicationEngine.hpp"
#include "Fakes/FakeQmlSingletons.hpp"
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("ContextPropertyTests")
{
    GIVEN("A fake qml application engine and list of qml singletons")
    {
        FakeQmlApplicationEngine qmlApplicationEngine;
        QObject propertyObject;
        QmlSingleton qmlSingleton("SingletonName", &propertyObject);

        WHEN("I call initialize on qmlSingletons")
        {
            qmlSingleton.registerTo(qmlApplicationEngine);

            THEN("qml singleton was added to the qmlApplicationEngine")
            {
                REQUIRE(qmlApplicationEngine.qmlSingleton("SingletonName") == &propertyObject);
            }
        }
    }
}
