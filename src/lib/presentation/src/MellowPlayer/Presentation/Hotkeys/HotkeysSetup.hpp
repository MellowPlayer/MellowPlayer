#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>
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

    class HotkeysSetup : public Domain::IInitializable
    {
        Q_OBJECT
    public:
        HotkeysSetup(Domain::IPlayer& player, Domain::Settings& settings, IMainWindow& mainWindow);
        ~HotkeysSetup();

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;
        QString toString() const override;

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
