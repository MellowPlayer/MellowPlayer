#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <qxtglobalshortcut.h>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

Hotkeys::Hotkeys(IPlayer& player, Settings& settings, IMainWindow& mainWindow)
        : _logger(Loggers::logger("Hotkeys")),
          _player(player),
          _mainWindow(mainWindow),
          _playShortcutSetting(settings.get(SettingKey::SHORTCUTS_PLAY)),
          _nextShortcutSetting(settings.get(SettingKey::SHORTCUTS_NEXT)),
          _previousShortcutSetting(settings.get(SettingKey::SHORTCUTS_PREVIOUS)),
          _favoriteShortcutSetting(settings.get(SettingKey::SHORTCUTS_FAVORITE)),
          _restoreWindowShortcutSetting(settings.get(SettingKey::SHORTCUTS_RESTORE_WINDOW))
{
    connect(&_playShortcutSetting, &Setting::valueChanged, this, &Hotkeys::updatePlayShortcut);
    connect(&_nextShortcutSetting, &Setting::valueChanged, this, &Hotkeys::updateNextShortcut);
    connect(&_previousShortcutSetting, &Setting::valueChanged, this, &Hotkeys::updatePreviousShorcut);
    connect(&_favoriteShortcutSetting, &Setting::valueChanged, this, &Hotkeys::updateFavoriteShortcut);
    connect(&_restoreWindowShortcutSetting, &Setting::valueChanged, this, &Hotkeys::updateRestoreWindowShortcut);
}

void Hotkeys::togglePlayPause()
{
    _player.togglePlayPause();
}

void Hotkeys::next()
{
    _player.next();
}

void Hotkeys::previous()
{
    _player.previous();
}

void Hotkeys::toggleFavoriteSong()
{
    _player.toggleFavoriteSong();
}

Hotkeys::~Hotkeys()
{
}

void Hotkeys::updatePlayShortcut() const
{
    _playShortcut->setShortcut(QKeySequence(_playShortcutSetting.value().toString()));
}

void Hotkeys::updateNextShortcut() const
{
    _nextShortcut->setShortcut(QKeySequence(_nextShortcutSetting.value().toString()));
}

void Hotkeys::updatePreviousShorcut() const
{
    _previousShortcut->setShortcut(QKeySequence(_previousShortcutSetting.value().toString()));
}

void Hotkeys::updateFavoriteShortcut() const
{
    _favoriteShortcut->setShortcut(QKeySequence(_favoriteShortcutSetting.value().toString()));
}

void Hotkeys::restoreWindow()
{
    _mainWindow.raise();
}

void Hotkeys::updateRestoreWindowShortcut() const
{
    _restoreWindowShortcut->setShortcut(QKeySequence(_restoreWindowShortcutSetting.value().toString()));
}

void Hotkeys::initialize(const IInitializable::ResultCallback& resultCallback)
{
    _playShortcut = std::make_shared<QxtGlobalShortcut>();
    updatePlayShortcut();
    connect(_playShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::togglePlayPause);

    _nextShortcut = std::make_shared<QxtGlobalShortcut>();
    updateNextShortcut();
    connect(_nextShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::next);

    _previousShortcut = std::make_shared<QxtGlobalShortcut>();
    updatePreviousShorcut();
    connect(_previousShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::previous);

    _favoriteShortcut = std::make_shared<QxtGlobalShortcut>();
    updateFavoriteShortcut();
    connect(_favoriteShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::toggleFavoriteSong);

    _restoreWindowShortcut = std::make_shared<QxtGlobalShortcut>();
    updateRestoreWindowShortcut();
    connect(_restoreWindowShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::restoreWindow);

#ifdef Q_OS_WIN
    _mediaPlayShortcut = std::make_shared<QxtGlobalShortcut>();
    _mediaPlayShortcut->setShortcut(QKeySequence(Qt::Key_MediaPlay));
    connect(_mediaPlayShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::togglePlayPause);

    _mediaNextShortcut = std::make_shared<QxtGlobalShortcut>();
    _mediaNextShortcut->setShortcut(QKeySequence(Qt::Key_MediaNext));
    connect(_mediaNextShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::next);

    _mediaPreviousShortcut = std::make_shared<QxtGlobalShortcut>();
    _mediaPreviousShortcut->setShortcut(QKeySequence(Qt::Key_MediaPrevious));
    connect(_mediaPreviousShortcut.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::previous);
#endif

    LOG_DEBUG(_logger, "hotkeys configured");
    resultCallback(true);
}

QString Hotkeys::toString() const
{
    return "Hotkeys";
}

void Hotkeys::cleanUp()
{
    _playShortcut = nullptr;
    _nextShortcut = nullptr;
    _previousShortcut = nullptr;
    _favoriteShortcut = nullptr;
    _restoreWindowShortcut = nullptr;

    _mediaPlayShortcut = nullptr;
    _mediaNextShortcut = nullptr;
    _mediaPreviousShortcut = nullptr;
}
