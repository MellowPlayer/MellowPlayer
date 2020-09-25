#include <Fakes/FakePlayer.hpp>
#include <Fakes/FakeSettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <UnitTests/Presentation/FakeMainWindow.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Tests;

TEST_CASE("SystemTrayIconTests")
{
    FakePlayer player;
    DependencyPool pool;
    FakeMainWindow mainWindow;

    SystemTrayIcon systemTrayIcon(player, mainWindow, pool.getSettings(), pool.getStreamingServicesViewModel());
    player.play();

    SECTION("don't show window onActivated with context menu")
    {
        systemTrayIcon.onActivated(QSystemTrayIcon::Context);
        REQUIRE(!mainWindow.isShown);
    }

    SECTION("show window onActivated with double click")
    {
        systemTrayIcon.onActivated(QSystemTrayIcon::DoubleClick);
        REQUIRE(mainWindow.isShown);
    }

    SECTION("show window onActivated with trigger")
    {
        systemTrayIcon.onActivated(QSystemTrayIcon::Trigger);
        REQUIRE(mainWindow.isShown);
    }

    SECTION("togglePlayPause call player")
    {
        systemTrayIcon.togglePlayPause();
        REQUIRE(player.playbackStatus() == PlaybackStatus::Paused);
    }

    SECTION("next call player")
    {
        systemTrayIcon.next();
        REQUIRE(player.trackIndex() == 1);
    }

    SECTION("previous call player")
    {
        systemTrayIcon.previous();
        REQUIRE(player.trackIndex() == -1);
    }

    SECTION("restoreWindow show window")
    {
        systemTrayIcon.restoreWindow();
        REQUIRE(mainWindow.isShown);
    }

    SECTION("quit quits the application")
    {
        systemTrayIcon.quit();
        REQUIRE(mainWindow.quitRequested);
    }

    SECTION("show icon")
    {
        systemTrayIcon.show();
    }
    SECTION("hide icon")
    {
        systemTrayIcon.hide();
    }
    SECTION("show message")
    {
        systemTrayIcon.showMessage("Title", "Message");
    }
}
