#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <MellowPlayer/Presentation/Notifications/PlayerNotifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>

using namespace fakeit;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

TEST_CASE("NotificationsTests", "[UnitTest]")
{
    MellowPlayer::Tests::DependencyPool pool;

    Settings& settings = pool.getSettings();
    PlayerNotifications sut(pool.getCurrentPlayer(), pool.getLocalAlbumArt(), pool.getNotificationPresenter(), pool.getStreamingServices(), pool.getSettings());

    Mock<LocalAlbumArt> localAlbumArtServiceSpy(pool.getLocalAlbumArt());
    Mock<IPlayer> playerSpy(pool.getCurrentPlayer());
    Mock<INotificationPresenter>& notificationPresenterMock = pool.getNotificationPresenterMock();

    Setting& playNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
    playNotifEnabled.setValue(true);
    Setting& pausedNotifEnabled = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
    pausedNotifEnabled.setValue(true);

    Song validSong("uniqueId", "songTitle", "artistName", "album", "artUrl", 50, false);
    REQUIRE(validSong.isValid());

    Song invalidSong("", "", "", "", "", 50, false);
    REQUIRE(!invalidSong.isValid());

    When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Playing);
    When(Method(localAlbumArtServiceSpy, isReady)).AlwaysReturn(true);
    When(Method(playerSpy, currentSong)).AlwaysReturn(&validSong);

    SECTION("display allowed notification")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(sut.display(notif));
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display disallowed notification")
    {
        playNotifEnabled.setValue(false);
        Notification notif{"title", "message", "", NotificationType::NewSong};
        REQUIRE(!sut.display(notif));
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("display current song changed notification if "
            "song is valid and "
            "player is playing and "
            "art is ready")
    {
        sut.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display current song changed notification if service notifications are disabled")
    {
        auto& currentPlayer = pool.getCurrentPlayer();
        pool.getSettingsStore().setValue(currentPlayer.serviceName() + "/notificationsEnabled", false);
        sut.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();
        pool.getSettingsStore().setValue(currentPlayer.serviceName() + "/notificationsEnabled", true);
    }

    SECTION("don't display current song changed notification if player is not "
            "playing")
    {
        When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Paused);
        sut.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("don't display current song changed notification if art is not ready")
    {
        When(Method(localAlbumArtServiceSpy, isReady)).AlwaysReturn(false);
        sut.onCurrentSongChanged(&validSong);
        Verify(Method(notificationPresenterMock, display)).Never();

        SECTION("display current song changed notification when album art is ready")
        {
            When(Method(localAlbumArtServiceSpy, isReady)).AlwaysReturn(true);
            sut.onCurrentSongUrlChanged();
            Verify(Method(notificationPresenterMock, display)).Once();
        }
    }

    SECTION("don't display current song changed notification if current song is "
            "invalid")
    {
        sut.onCurrentSongChanged(&invalidSong);
        Verify(Method(notificationPresenterMock, display)).Never();
    }

    SECTION("display current song changed notification when playback status "
            "changed to Playing")
    {
        sut.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("display paused notification when playback status changed to Paused")
    {
        When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Paused);
        sut.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Once();
    }

    SECTION("don't display paused notification when playback status changed to "
            "Stopped")
    {
        When(Method(playerSpy, playbackStatus)).AlwaysReturn(PlaybackStatus::Stopped);
        sut.onPlaybackStatusChanged();
        Verify(Method(notificationPresenterMock, display)).Never();
    }
}
