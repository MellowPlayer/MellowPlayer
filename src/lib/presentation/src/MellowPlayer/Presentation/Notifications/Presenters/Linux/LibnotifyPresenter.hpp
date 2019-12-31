#pragma once

#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

struct _NotifyNotification;

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Presentation
{
    class IMainWindow;
    struct Notification;
    class ISystemTrayIcon;

    class LibnotifyPresenter : public INotificationPresenter
    {
    public:
        explicit LibnotifyPresenter(IMainWindow& mainWindow, Domain::IWorkDispatcher& workDispatcher, ISystemTrayIcon& systemTrayIcon);

        void initialize() override;
        bool display(const Notification& notification) override;

        static void onActionCallback();

    private:
        void checkSupportForActions();

        Domain::ILogger& _logger;
        IMainWindow& _mainWindow;
        Domain::IWorkDispatcher& _workDispatcher;
        _NotifyNotification* _previousNotification;
        ISystemTrayIcon& _systemTrayIcon;
        bool _actionsSupported = true;
        static LibnotifyPresenter* _instance;
    };
}
