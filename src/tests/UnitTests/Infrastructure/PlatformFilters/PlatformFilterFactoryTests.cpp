#include <MellowPlayer/Infrastructure/PlatformFilters/IPlatformFilter.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilterFactory.hpp>
#include <QList>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("PlatformFilterFactoryTests")
{
    GIVEN("a PlatformFilterFactory instance")
    {
        PlatformFilterFactory factory;

        WHEN("creating a valid filter")
        {
            QList<Filter> filters = {Filter::All, Filter::Linux, Filter::Windows, Filter::OSX};

            for (auto filter : filters)
            {
                THEN(QString("filter is not nullptr (%1)").arg(static_cast<int>(filter)).toStdString())
                {
                    REQUIRE(factory.create(filter) != nullptr);
                }
            }
        }
    }
}
