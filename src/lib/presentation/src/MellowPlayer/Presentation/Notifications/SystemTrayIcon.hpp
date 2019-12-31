#pragma once

#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <QMenu>
#include <QSystemTrayIcon>

namespace MellowPlayer::Domain
{
    class ILogger;
    class IPlayer;
    class Setting;
    class Settings;
}

class SystemTrayIconStrings : public QObject
{
    Q_OBJECT
public:
    QString playPause() const;
    QString next() const;
    QString previous() const;
    QString restoreWindow() const;
    QString quit() const;
};

namespace MellowPlayer::Infrastructure
{
    class IApplication;
}

namespace MellowPlayer::Presentation
{
    class IMainWindow;

    class SystemTrayIcon : public ISystemTrayIcon
    {
        Q_OBJECT
    public:
        SystemTrayIcon(Domain::IPlayer& player, IMainWindow& mainWindow, Domain::Settings& settings);

        void show() override;
        void hide() override;
        void showMessage(const QString& title, const QString& message) override;

    public slots:
        void onActivated(QSystemTrayIcon::ActivationReason reason);
        void togglePlayPause();
        void next();
        void previous();
        void restoreWindow();
        void quit();

    private slots:
        void onShowTrayIconSettingValueChanged();
        void updateIcon();

    private:
        void setUpMenu();

        Domain::ILogger& _logger;
        Domain::IPlayer& _player;
        IMainWindow& _mainWindow;
        Domain::Settings& _settings;
        Domain::Setting& _showTrayIconSetting;
        Domain::Setting& _customTrayIconSetting;

        QSystemTrayIcon _qSystemTrayIcon;
        QMenu _menu;
        QAction* _playPauseAction;
        QAction* _previousSongAction;
        QAction* _nextSongAction;
        QAction* _restoreWindowAction;
        QAction* _quitApplicationAction;
    };
}
