#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyStrings.hpp>
#undef Q_SIGNALS
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <libnotify/notify.h>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

LibnotifyPresenter* LibnotifyPresenter::_instance = nullptr;

void notify_action_callback(NotifyNotification*, char*, gpointer)
{
    LibnotifyPresenter::onActionCallback();
}

LibnotifyPresenter::LibnotifyPresenter(IMainWindow& mainWindow, IWorkDispatcher& workDispatcher, ISystemTrayIcon& trayIcon)
        : _logger(Loggers::logger("LibnotifyPresenter")),
          _mainWindow(mainWindow),
          _workDispatcher(workDispatcher),
          _previousNotification(nullptr),
          _systemTrayIcon(trayIcon)
{
    _instance = this;
}

void LibnotifyPresenter::initialize()
{
    notify_init("MellowPlayer");
    checkSupportForActions();
    _systemTrayIcon.show();
    LOG_DEBUG(_logger, "service started")
}

void LibnotifyPresenter::checkSupportForActions()
{
    GList* caps = notify_get_server_caps();
    if (g_list_find_custom(caps, "actions", (GCompareFunc) g_strcmp0) == NULL)
        _actionsSupported = false;
    g_list_free_full(caps, g_free);
}

bool LibnotifyPresenter::display(const Notification& notification)
{
    Q_UNUSED(notification)
    static LibnotifyStrings strings;

    if (_previousNotification)
        notify_notification_close(_previousNotification, 0);

    QString title = "MellowPlayer - " + notification.title;
    NotifyNotification* n =
            notify_notification_new(title.toStdString().c_str(), notification.description.toStdString().c_str(), notification.icon.toStdString().c_str());
    notify_notification_set_timeout(n, 5000);
    string openStr = strings.open();
    if (_actionsSupported)
        notify_notification_add_action(n, "open", strings.open().c_str(), (NotifyActionCallback) notify_action_callback, nullptr, nullptr);
    notify_notification_set_hint(n, "desktop-entry", g_variant_new_string("mellowplayer"));

    _workDispatcher.invoke([=]() { notify_notification_show(n, 0); });

    _previousNotification = n;

    return true;
}

void LibnotifyPresenter::onActionCallback()
{
    _instance->_mainWindow.raise();
}
