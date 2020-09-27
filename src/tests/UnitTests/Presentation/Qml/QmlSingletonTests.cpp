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
        auto qmlSingletons = std::make_shared<FakeQmlSingletons>();
        qmlSingletons->setQmlApplicationEngine(&qmlApplicationEngine);

        WHEN("I create a qml singleton")
        {
            QmlSingleton qmlSingleton("ContextPropertyName", &propertyObject, *qmlSingletons);

            THEN("propertyObject has been added to the qml singletons")
            {
                REQUIRE(qmlSingletons->contains(qmlSingleton));
            }

            AND_WHEN("I call initialize on qmlSingletons")
            {
                qmlSingletons->registerToQml();

                THEN("qml singleton was added to the qmlApplicationEngine")
                {
                    REQUIRE(qmlApplicationEngine.qmlSingleton("ContextPropertyName") == &propertyObject);
                }
            }
        }
    }
}
