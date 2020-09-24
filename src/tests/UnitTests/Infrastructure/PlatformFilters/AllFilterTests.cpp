#include <MellowPlayer/Infrastructure/PlatformFilters/AllFilter.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("AllFilterTests")
{
    GIVEN("an AllFilter instance")
    {
        AllFilter filter;

        WHEN("on any platform")
        {
            THEN("match always returns true")
            {
                REQUIRE(filter.match());
            }
        }
    }
}
