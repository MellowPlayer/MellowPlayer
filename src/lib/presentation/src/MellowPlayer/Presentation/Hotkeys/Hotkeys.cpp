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
        : logger_(Loggers::logger("Hotkeys")),
          player_(player),
          mainWindow_(mainWindow),
          playShortcutSetting_(settings.get(SettingKey::SHORTCUTS_PLAY)),
          nextShortcutSetting_(settings.get(SettingKey::SHORTCUTS_NEXT)),
          previousShortcutSetting_(settings.get(SettingKey::SHORTCUTS_PREVIOUS)),
          favoriteShortcutSetting_(settings.get(SettingKey::SHORTCUTS_FAVORITE)),
          restoreWindowShortcutSetting_(settings.get(SettingKey::SHORTCUTS_RESTORE_WINDOW))
{
    connect(&playShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updatePlayShortcut);
    connect(&nextShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updateNextShortcut);
    connect(&previousShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updatePreviousShorcut);
    connect(&favoriteShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updateFavoriteShortcut);
    connect(&restoreWindowShortcutSetting_, &Setting::valueChanged, this, &Hotkeys::updateRestoreWindowShortcut);
}

void Hotkeys::togglePlayPause()
{
    player_.togglePlayPause();
}

void Hotkeys::next()
{
    player_.next();
}

void Hotkeys::previous()
{
    player_.previous();
}

void Hotkeys::toggleFavoriteSong()
{
    player_.toggleFavoriteSong();
}

Hotkeys::~Hotkeys()
{
}

void Hotkeys::updatePlayShortcut() const
{
    playShortcut_->setShortcut(QKeySequence(playShortcutSetting_.value().toString()));
}

void Hotkeys::updateNextShortcut() const
{
    nextShortcut_->setShortcut(QKeySequence(nextShortcutSetting_.value().toString()));
}

void Hotkeys::updatePreviousShorcut() const
{
    previousShortcut_->setShortcut(QKeySequence(previousShortcutSetting_.value().toString()));
}

void Hotkeys::updateFavoriteShortcut() const
{
    favoriteShortcut_->setShortcut(QKeySequence(favoriteShortcutSetting_.value().toString()));
}

void Hotkeys::restoreWindow()
{
    mainWindow_.raise();
}

void Hotkeys::updateRestoreWindowShortcut() const
{
    restoreWindowShortcut_->setShortcut(QKeySequence(restoreWindowShortcutSetting_.value().toString()));
}

void Hotkeys::initialize(const IInitializable::ResultCallback& resultCallback)
{
    playShortcut_ = std::make_shared<QxtGlobalShortcut>();
    updatePlayShortcut();
    connect(playShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::togglePlayPause);

    nextShortcut_ = std::make_shared<QxtGlobalShortcut>();
    updateNextShortcut();
    connect(nextShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::next);

    previousShortcut_ = std::make_shared<QxtGlobalShortcut>();
    updatePreviousShorcut();
    connect(previousShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::previous);

    favoriteShortcut_ = std::make_shared<QxtGlobalShortcut>();
    updateFavoriteShortcut();
    connect(favoriteShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::toggleFavoriteSong);

    restoreWindowShortcut_ = std::make_shared<QxtGlobalShortcut>();
    updateRestoreWindowShortcut();
    connect(restoreWindowShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::restoreWindow);

#ifdef Q_OS_WIN
    mediaPlayShortcut_ = std::make_shared<QxtGlobalShortcut>();
    mediaPlayShortcut_->setShortcut(QKeySequence(Qt::Key_MediaPlay));
    connect(mediaPlayShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::togglePlayPause);

    mediaNextShortcut_ = std::make_shared<QxtGlobalShortcut>();
    mediaNextShortcut_->setShortcut(QKeySequence(Qt::Key_MediaNext));
    connect(mediaNextShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::next);

    mediaPreviousShortcut_ = std::make_shared<QxtGlobalShortcut>();
    mediaPreviousShortcut_->setShortcut(QKeySequence(Qt::Key_MediaPrevious));
    connect(mediaPreviousShortcut_.get(), &QxtGlobalShortcut::activated, this, &Hotkeys::previous);
#endif

    LOG_DEBUG(logger_, "hotkeys configured");
    resultCallback(true);
}

QString Hotkeys::toString() const
{
    return "Hotkeys";
}

void Hotkeys::cleanUp()
{
    playShortcut_ = nullptr;
    nextShortcut_ = nullptr;
    previousShortcut_ = nullptr;
    favoriteShortcut_ = nullptr;
    restoreWindowShortcut_ = nullptr;

    mediaPlayShortcut_ = nullptr;
    mediaNextShortcut_ = nullptr;
    mediaPreviousShortcut_ = nullptr;
}
