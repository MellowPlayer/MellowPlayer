#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilterFactory.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilters.hpp>
#include <QObject>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("PlatformFiltersTests")
{
    GIVEN("a PlatformFilters instance")
    {
        PlatformFilters filters;

        WHEN("filter is 'All'")
        {
            QString filter = "All";

            THEN("match always returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
        WHEN("filter is 'Linux'")
        {
            QString filter = "Linux";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Windows'")
        {
            QString filter = "Windows";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-Windows'")
        {
            QString filter = "Linux-Windows";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'OSX'")
        {
            QString filter = "OSX";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX'")
        {
            QString filter = "Linux-,OSX";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX-Windows'")
        {
            QString filter = "Linux-OSX-Windows";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }
#endif

#ifdef Q_OS_WIN
        WHEN("filter is 'Windows'")
        {
            QString filter = "Windows";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux'")
        {
            QString filter = "Linux";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'OSX'")
        {
            QString filter = "OSX";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-Windows'")
        {
            QString filter = "Linux-Windows";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX'")
        {
            QString filter = "Linux-OSX";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX-Windows'")
        {
            QString filter = "Linux-OSX-Windows";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }
#endif

#ifdef Q_OS_OSX
        WHEN("filter is 'OSX'")
        {
            QString filter = "OSX";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Windows'")
        {
            QString filter = "Windows";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux'")
        {
            QString filter = "Linux";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-Windows'")
        {
            QString filter = "Linux-Windows";

            THEN("match returns false")
            {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX'")
        {
            QString filter = "Linux-OSX";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX-Windows'")
        {
            QString filter = "Linux-OSX-Windows";

            THEN("match returns true")
            {
                REQUIRE(filters.match(filter));
            }
        }
#endif
    }
}
