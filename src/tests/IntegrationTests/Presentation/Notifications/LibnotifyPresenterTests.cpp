#ifdef USE_LIBNOTIFY

#    include <Fakes/FakeWorkDispatcher.hpp>
#    include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#    include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyPresenter.hpp>
#    include <Mocks/SystemTrayIconMock.hpp>
#    include <UnitTests/Presentation/FakeMainWindow.hpp>
#    include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

TEST_CASE("LibnotifyPresenterTests")
{
    FakeMainWindow mainWindow;
    FakeWorkDispatcher workDispatcher;
    LibnotifyPresenter presenter(mainWindow, workDispatcher);
    presenter.initialize();

    SECTION("display test")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        presenter.display(notif);
        presenter.display(notif);
    }

    SECTION("action callback show main window")
    {
        presenter.onActionCallback();
        REQUIRE(mainWindow.isShown);
    }
}

#endif
