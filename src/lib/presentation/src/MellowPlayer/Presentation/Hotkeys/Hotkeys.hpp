#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <QObject>
#include <memory>

class QHotkey;

namespace MellowPlayer::Domain
{
    class IPlayer;
    class ILogger;
    class Setting;
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class IMainWindow;

    class IHotkeys : public QObject
    {
    public:
        virtual ~IHotkeys() = default;

        virtual void grab() = 0;
        virtual void unGrab() = 0;
    };

    class Hotkeys : public IHotkeys
    {
        Q_OBJECT
    public:
        Hotkeys(Domain::IPlayer& player, Domain::Settings& settings, IMainWindow& mainWindow);

        void grab() override;
        void unGrab() override;

    private slots:
        void togglePlayPause();
        void next();
        void previous();
        void toggleFavoriteSong();
        void restoreWindow();

    private:
        void updateFavoriteShortcut() const;
        void updatePreviousShorcut() const;
        void updateNextShortcut() const;
        void updatePlayShortcut() const;
        void updateRestoreWindowShortcut() const;

        Domain::ILogger& _logger;
        Domain::IPlayer& _player;
        IMainWindow& _mainWindow;

        std::shared_ptr<QHotkey> _playShortcut;
        std::shared_ptr<QHotkey> _nextShortcut;
        std::shared_ptr<QHotkey> _previousShortcut;
        std::shared_ptr<QHotkey> _favoriteShortcut;
        std::shared_ptr<QHotkey> _restoreWindowShortcut;
        std::shared_ptr<QHotkey> _mediaPlayShortcut;
        std::shared_ptr<QHotkey> _mediaNextShortcut;
        std::shared_ptr<QHotkey> _mediaPreviousShortcut;

        Domain::Setting& _playShortcutSetting;
        Domain::Setting& _nextShortcutSetting;
        Domain::Setting& _previousShortcutSetting;
        Domain::Setting& _favoriteShortcutSetting;
        Domain::Setting& _restoreWindowShortcutSetting;
    };
}
