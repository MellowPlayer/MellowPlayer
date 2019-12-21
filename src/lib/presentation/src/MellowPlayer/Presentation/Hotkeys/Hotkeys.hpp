#pragma once

#include <MellowPlayer/Presentation/Hotkeys/IHotkeys.hpp>
#include <QObject>
#include <memory>

class QxtGlobalShortcut;

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

    class Hotkeys : public IHotkeys
    {
        Q_OBJECT
    public:
        Hotkeys(Domain::IPlayer& player, Domain::Settings& settings, IMainWindow& mainWindow);
        ~Hotkeys();

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;
        QString toString() const override;

    public slots:
        void togglePlayPause() override;
        void next() override;
        void previous() override;
        void toggleFavoriteSong() override;
        void restoreWindow() override;

    private:
        void updateFavoriteShortcut() const;
        void updatePreviousShorcut() const;
        void updateNextShortcut() const;
        void updatePlayShortcut() const;
        void updateRestoreWindowShortcut() const;

        Domain::ILogger& _logger;
        Domain::IPlayer& _player;
        IMainWindow& _mainWindow;

        std::shared_ptr<QxtGlobalShortcut> _playShortcut;
        std::shared_ptr<QxtGlobalShortcut> _nextShortcut;
        std::shared_ptr<QxtGlobalShortcut> _previousShortcut;
        std::shared_ptr<QxtGlobalShortcut> _favoriteShortcut;
        std::shared_ptr<QxtGlobalShortcut> _restoreWindowShortcut;
        std::shared_ptr<QxtGlobalShortcut> _mediaPlayShortcut;
        std::shared_ptr<QxtGlobalShortcut> _mediaNextShortcut;
        std::shared_ptr<QxtGlobalShortcut> _mediaPreviousShortcut;

        Domain::Setting& _playShortcutSetting;
        Domain::Setting& _nextShortcutSetting;
        Domain::Setting& _previousShortcutSetting;
        Domain::Setting& _favoriteShortcutSetting;
        Domain::Setting& _restoreWindowShortcutSetting;
    };
}
