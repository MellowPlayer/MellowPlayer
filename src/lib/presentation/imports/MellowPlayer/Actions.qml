pragma Singleton
import QtQuick 2.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

QtObject {
    id: actions

    // MainWindowViewModel actions
    property Action toggleSelectServiceDrawer
    property Action toggleListeningHistory
    property Action openSettings
    property Action createNewPlugin
    property Action reportIssue
    property Action toggleToolBar
    property Action showDevtools
    property Action checkForUpdates
    property Action showAbout
    property Action quit

    // Current web view actions
    property Action goBack
    property Action goForward
    property Action reload
    property Action goHome

    // Player actions
    property Action toggleFavoriteSong: Action {
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_FAVORITE).value
        enabled: CurrentPlayer.canAddToFavorites

        onTriggered: CurrentPlayer.toggleFavoriteSong()
    }
    property Action skipToPreviousSong: Action {
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_PREVIOUS).value
        enabled: CurrentPlayer.canGoPrevious && CurrentPlayer.active

        onTriggered: CurrentPlayer.previous()
    }
    property Action playPause: Action {
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_PLAY).value
        enabled: !CurrentPlayer.isStopped || CurrentPlayer.active

        onTriggered: CurrentPlayer.togglePlayPause()
    }
    property Action skipToNextSong: Action {
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_NEXT).value
        enabled: CurrentPlayer.canGoNext && CurrentPlayer.active

        onTriggered: CurrentPlayer.next()
    }

    // Other actions
    property Action toggleNotifications: Action {
        property SettingViewModel setting: SettingsViewModel.get(SettingKey.NOTIFICATIONS_ENABLED)

        checkable: true
        checked: setting.value
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_NOTIFICATIONS).value

        onToggled: setting.value = checked
    }
}
