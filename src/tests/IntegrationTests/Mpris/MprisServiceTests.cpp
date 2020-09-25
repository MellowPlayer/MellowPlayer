#include <QtCore>
#include <catch2/catch.hpp>
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#    include <Fakes/FakeAlbumArtDownloader.hpp>
#    include <Fakes/FakeStreamingServiceLoader.hpp>
#    include <Fakes/FakeStreamingServiceWatcher.hpp>
#    include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#    include <MellowPlayer/Domain/Player/Players.hpp>
#    include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#    include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#    include <MellowPlayer/Presentation/Mpris/Linux/MprisStartup.hpp>
#    include <QtDBus/QDBusConnection>
#    include <UnitTests/Presentation/FakeMainWindow.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

TEST_CASE("MprisServiceTests", "[IntegrationTest]")
{
    FakeStreamingServiceLoader streamingServiceLoader;
    FakeStreamingServiceWatcher streamingServiceWatcher;
    StreamingServices streamingServices(streamingServiceLoader, streamingServiceWatcher);
    Players players(streamingServices);
    CurrentPlayer player(players, streamingServices);
    FakeAlbumArtDownloader albumArtDownloader;
    LocalAlbumArt localAlbumArt(player, albumArtDownloader);
    FakeMainWindow mainWindow;

    MprisStartup mprisService(player, localAlbumArt, mainWindow);
    SECTION("start should succeed the first time")
    {
        if (QDBusConnection::sessionBus().isConnected())
        {
            bool success = mprisService.start();
            REQUIRE(success);

            SECTION("should fail the second time ")
            {
                success = mprisService.start();
                REQUIRE(!success);
            }
        }
    }
}

#endif
