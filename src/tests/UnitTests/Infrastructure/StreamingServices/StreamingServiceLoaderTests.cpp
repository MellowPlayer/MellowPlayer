#include <Fakes/FakeSettingsStore.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Tests;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("StreamingServiceLoaderTests")
{
    DependencyPool pool;
    StreamingServiceLoader loader(pool.getSettings());

    SECTION("load")
    {
        auto services = loader.load();
        REQUIRE(services.count() > 1);
    }
}
