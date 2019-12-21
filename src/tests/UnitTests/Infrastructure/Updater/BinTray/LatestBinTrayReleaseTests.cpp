#include "Fakes/FakeBinTrayHttpClient.hpp"
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("Get latest release")
{
    FakeBinTrayHttpClient httpClient;
    LatestBinTrayRelease sut(httpClient);
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

            AND_THEN("Latest stable release version is correct")
            {
                REQUIRE(latestRelease->name().toStdString() == httpClient.expectedVersion(updateChannel).toStdString());
            }

            AND_THEN("Latest stable release date is correct")
            {
                REQUIRE(latestRelease->date() == httpClient.expectedDate(updateChannel).toString("MMMM dd yyyy"));
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

            AND_THEN("Latest stable release version is correct")
            {
                REQUIRE(latestRelease->name().toStdString() == httpClient.expectedVersion(updateChannel).toStdString());
            }

            AND_THEN("Latest stable release date is correct")
            {
                REQUIRE(latestRelease->date() == httpClient.expectedDate(updateChannel).toString("MMMM dd yyyy"));
            }
        }
    }
}
