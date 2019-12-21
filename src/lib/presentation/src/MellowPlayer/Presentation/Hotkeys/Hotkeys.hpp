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

        Domain::ILogger& logger_;
        Domain::IPlayer& player_;
        IMainWindow& mainWindow_;

        std::shared_ptr<QxtGlobalShortcut> playShortcut_;
        std::shared_ptr<QxtGlobalShortcut> nextShortcut_;
        std::shared_ptr<QxtGlobalShortcut> previousShortcut_;
        std::shared_ptr<QxtGlobalShortcut> favoriteShortcut_;
        std::shared_ptr<QxtGlobalShortcut> restoreWindowShortcut_;
        std::shared_ptr<QxtGlobalShortcut> mediaPlayShortcut_;
        std::shared_ptr<QxtGlobalShortcut> mediaNextShortcut_;
        std::shared_ptr<QxtGlobalShortcut> mediaPreviousShortcut_;

        Domain::Setting& playShortcutSetting_;
        Domain::Setting& nextShortcutSetting_;
        Domain::Setting& previousShortcutSetting_;
        Domain::Setting& favoriteShortcutSetting_;
        Domain::Setting& restoreWindowShortcutSetting_;
    };
}
