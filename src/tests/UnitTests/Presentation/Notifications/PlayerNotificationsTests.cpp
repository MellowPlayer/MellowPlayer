#include <Fakes/FakeAlbumArtDownloader.hpp>
#include <Fakes/FakeLocalAlbumArt.hpp>
#include <Fakes/FakePlayer.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <MellowPlayer/Presentation/Notifications/PlayerNotifications.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

TEST_CASE("NotificationsTests", "[UnitTest]")
{
    MellowPlayer::Tests::DependencyPool pool;

    Settings& settings = pool.getSettings();
    FakeNotificationPresenter notificationPresenter;
    FakePlayer player;
    FakeLocalAlbumArt localAlbumArt;
    PlayerNotifications sut(player, localAlbumArt, notificationPresenter, pool.getStreamingServices(), settings);

    Setting& playNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
    playNotifEnabled.setValue(true);

    Setting& pausedNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
    pausedNotifEnabled.setValue(true);

    Song validSong("uniqueId", "songTitle", "artistName", "album", "artUrl", 50, false);
    Song invalidSong("", "", "", "", "", 50, false);

    sut.listen();

    SECTION("display allowed notification")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(sut.display(notif));
        REQUIRE(notificationPresenter.displayedNotifications().count() == 1);;
    }

    SECTION("display disallowed notification")
    {
        playNotifEnabled.setValue(false);
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(!sut.display(notif));
        REQUIRE(notificationPresenter.displayedNotifications().count() == 0);;
    }

    SECTION("display current song changed notification if "
            "song is valid and "
            "player is playing and "
            "art is ready")
    {
        player.play();
        localAlbumArt.setReady(true);
        notificationPresenter.clearDisplayedNotifications();

        player.setCurrentSong(&validSong);

        REQUIRE(notificationPresenter.displayedNotifications().count() == 1);;
    }

    SECTION("don't display current song changed notification if service notifications are disabled")
    {
        auto& currentPlayer = pool.getCurrentPlayer();
        pool.getSettingsStore().setValue(currentPlayer.serviceName() + "/notificationsEnabled", false);
        player.setCurrentSong(&validSong);
        REQUIRE(notificationPresenter.displayedNotifications().count() == 0);;
        pool.getSettingsStore().setValue(currentPlayer.serviceName() + "/notificationsEnabled", true);
    }

    SECTION("don't display current song changed notification if player is not playing")
    {
        player.pause();
        notificationPresenter.clearDisplayedNotifications();

        player.setCurrentSong(&validSong);
        REQUIRE(notificationPresenter.displayedNotifications().count() == 0);;
    }

    SECTION("don't display current song changed notification if art is not ready")
    {
        localAlbumArt.setReady(false);
        player.play();
        notificationPresenter.clearDisplayedNotifications();

        player.setCurrentSong(&validSong);
        REQUIRE(notificationPresenter.displayedNotifications().count() == 0);;

        SECTION("display current song changed notification when album art is ready")
        {
            localAlbumArt.setReady(true);
            notificationPresenter.clearDisplayedNotifications();

            sut.onCurrentSongUrlChanged();
            REQUIRE(notificationPresenter.displayedNotifications().count() == 1);;
        }
    }

    SECTION("don't display current song changed notification if current song is "
            "invalid")
    {
        player.setCurrentSong(&invalidSong);
        REQUIRE(notificationPresenter.displayedNotifications().count() == 0);;
    }

    SECTION("display current song changed notification when playback status "
            "changed to Playing")
    {
        player.togglePlayPause();
        REQUIRE(notificationPresenter.displayedNotifications().count() == 1);;
    }

    SECTION("display paused notification when playback status changed to Paused")
    {
        player.pause();
        REQUIRE(notificationPresenter.displayedNotifications().count() == 1);;
    }

    SECTION("don't display paused notification when playback status changed to "
            "Stopped")
    {
        player.stop();
        REQUIRE(notificationPresenter.displayedNotifications().count() == 0);;
    }
}
