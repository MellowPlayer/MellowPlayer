#include <Fakes/FakeSystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Presentation;

TEST_CASE("SystemTrayIconPresenterTests")
{
    FakeSystemTrayIcon systemTrayIcon;
    SystemTrayIconPresenter presenter(systemTrayIcon);
    presenter.initialize();
    REQUIRE(systemTrayIcon.isVisible());

    SECTION("display test")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        presenter.display(notif);
        REQUIRE(systemTrayIcon.messages().first() == SystemTrayIconMessage("title", "message"));
    }
}
