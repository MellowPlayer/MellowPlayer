#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

SCENARIO("UserScriptFactoryTests")
{
    GIVEN("an instance of userscript factory")
    {
        UserScriptFactory factory;

        WHEN("call create")
        {
            auto* userScript = factory.create();

            THEN("created user script is not null")
            {
                REQUIRE(userScript != nullptr);
            }
        }
    }
}