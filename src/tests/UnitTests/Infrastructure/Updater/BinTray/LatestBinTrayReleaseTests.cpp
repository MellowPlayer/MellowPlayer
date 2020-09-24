#include "Fakes/FakeBinTrayHttpClient.hpp"
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("Get latest release")
{
    auto httpClient = std::make_unique<FakeBinTrayHttpClient>();
    LatestBinTrayRelease sut(std::move(httpClient));
    const Release* latestRelease;
    QObject::connect(&sut, &ILatestRelease::received, [&](const Release* release) { latestRelease = release; });

    QList<UpdateChannel> updateChannels = {UpdateChannel::Stable, UpdateChannel::Continuous};

    WHEN("We get the latest stable release")
    {
        UpdateChannel updateChannel = UpdateChannel::Stable;
        sut.setChannel(updateChannel);
        sut.get();

        THEN("Latest release is not null")
        {
            REQUIRE(latestRelease != nullptr);

            AND_THEN("Latest stable release contains two assets")
            {
                REQUIRE(latestRelease->assets().count() == 2);
                REQUIRE(latestRelease->assets()[0].isWindowsInstaller());
                REQUIRE(latestRelease->assets()[1].isAppImage());
            }
        }
    }

    WHEN("We get the latest continuous release")
    {
        UpdateChannel updateChannel = UpdateChannel::Continuous;
        sut.setChannel(updateChannel);
        sut.get();

        THEN("Latest release is not null")
        {
            REQUIRE(latestRelease != nullptr);

            AND_THEN("Latest stable release contains two assets")
            {
                REQUIRE(latestRelease->assets().count() == 2);
                REQUIRE(latestRelease->assets()[0].isWindowsInstaller());
                REQUIRE(latestRelease->assets()[1].isAppImage());
            }
        }
    }
}
