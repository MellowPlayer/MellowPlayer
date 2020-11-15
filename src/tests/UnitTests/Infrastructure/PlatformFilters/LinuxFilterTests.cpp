#include <MellowPlayer/Infrastructure/PlatformFilters/LinuxFilter.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("LinuxFilterTests")
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    GIVEN("the test runs on GNU/Linux")
    {
        LinuxFilter filter;

        THEN("match returns true")
        {
            REQUIRE(filter.match());
        }
    }
#else
    GIVEN("the test does not run on GNU/Linux")
    {
        WHEN("using LinuxFilter")
        {
            LinuxFilter filter;

            THEN("match returns false")
            {
                REQUIRE(!filter.match());
            }
        }
    }
#endif
}
