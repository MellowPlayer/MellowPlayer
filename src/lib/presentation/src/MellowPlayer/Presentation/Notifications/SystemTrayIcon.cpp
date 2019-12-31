#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/IconProvider.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

SystemTrayIcon::SystemTrayIcon(IPlayer& player, IMainWindow& mainWindow, Settings& settings)
        : _logger(Loggers::logger("SystemTrayIcon")),
          _player(player),
          _mainWindow(mainWindow),
          _settings(settings),
          _showTrayIconSetting(settings.get(SettingKey::APPEARANCE_SHOW_TRAY_ICON)),
          _customTrayIconSetting(settings.get(SettingKey::APPEARANCE_CUSTOM_TRAY_ICON)),
          _qSystemTrayIcon(IconProvider::trayIcon())
{
    connect(&_qSystemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayIcon::onActivated);
    connect(&_showTrayIconSetting, &Setting::valueChanged, this, &SystemTrayIcon::onShowTrayIconSettingValueChanged);
    connect(&_customTrayIconSetting, &Setting::valueChanged, this, &SystemTrayIcon::updateIcon);
    setUpMenu();
    updateIcon();
}

void SystemTrayIcon::updateIcon()
{
    _qSystemTrayIcon.setIcon(_customTrayIconSetting.value().toString() == "" ? IconProvider::trayIcon() : QIcon(_customTrayIconSetting.value().toString()));
}

void SystemTrayIcon::show()
{
    LOG_DEBUG(_logger, "show");
    if (_showTrayIconSetting.value().toBool() && qgetenv("QT_QPA_PLATFORM") != QByteArray("offscreen"))
        _qSystemTrayIcon.show();
}

void SystemTrayIcon::hide()
{
    LOG_DEBUG(_logger, "hide");
    _qSystemTrayIcon.hide();
}

void SystemTrayIcon::showMessage(const QString& title, const QString& message)
{
    LOG_DEBUG(_logger, "show message: " + title + " - " + message);
    _qSystemTrayIcon.showMessage(title, message);
}

void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    LOG_WARN(_logger, "activated" << reason);
    if (reason == QSystemTrayIcon::DoubleClick || reason == QSystemTrayIcon::Trigger)
        _mainWindow.raise();
}

void SystemTrayIcon::setUpMenu()
{
    SystemTrayIconStrings strings;
    _playPauseAction = _menu.addAction(IconProvider::play(), strings.playPause());
    connect(_playPauseAction, &QAction::triggered, this, &SystemTrayIcon::togglePlayPause);

    _nextSongAction = _menu.addAction(IconProvider::next(), strings.next());
    connect(_nextSongAction, &QAction::triggered, this, &SystemTrayIcon::next);

    _previousSongAction = _menu.addAction(IconProvider::previous(), strings.previous());
    connect(_previousSongAction, &QAction::triggered, this, &SystemTrayIcon::previous);

    _menu.addSeparator();

    _restoreWindowAction = _menu.addAction(IconProvider::restoreWindow(), strings.restoreWindow());
    connect(_restoreWindowAction, &QAction::triggered, this, &SystemTrayIcon::restoreWindow);

    _menu.addSeparator();

    _quitApplicationAction = _menu.addAction(IconProvider::quit(), strings.quit());
    connect(_quitApplicationAction, &QAction::triggered, this, &SystemTrayIcon::quit);

    _qSystemTrayIcon.setContextMenu(&_menu);
}

void SystemTrayIcon::togglePlayPause()
{
    LOG_DEBUG(_logger, "togglePlayPause");
    _player.togglePlayPause();
}

void SystemTrayIcon::next()
{
    LOG_DEBUG(_logger, "next");
    _player.next();
}

void SystemTrayIcon::previous()
{
    LOG_DEBUG(_logger, "previous");
    _player.previous();
}

void SystemTrayIcon::restoreWindow()
{
    LOG_DEBUG(_logger, "restore window");
    _mainWindow.raise();
}

void SystemTrayIcon::quit()
{
    LOG_DEBUG(_logger, "quit");
    _mainWindow.requestQuit();
}

void SystemTrayIcon::onShowTrayIconSettingValueChanged()
{
    if (_showTrayIconSetting.value().toBool())
        show();
    else
        hide();
}

QString SystemTrayIconStrings::playPause() const
{
    return tr("Play/Pause");
}

QString SystemTrayIconStrings::next() const
{
    return tr("Next");
}

QString SystemTrayIconStrings::previous() const
{
    return tr("Previous");
}

QString SystemTrayIconStrings::restoreWindow() const
{
    return tr("Restore window");
}

QString SystemTrayIconStrings::quit() const
{
    return tr("Quit");
}
