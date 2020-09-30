pragma Singleton
import QtQuick 2.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

QtObject {
    id: actions

    // MainWindow actions
    property Action toggleCurrentPage
    property Action openListeningHistory
    property Action openSettings
    property Action createNewPlugin
    property Action reportIssue
    property Action toggleToolBar
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
        shortcut: App.settings.get(SettingKey.SHORTCUTS_FAVORITE).value
        enabled: CurrentPlayer.canAddToFavorites

        onTriggered: CurrentPlayer.toggleFavoriteSong()
    }
    property Action skipToPreviousSong: Action {
        shortcut: App.settings.get(SettingKey.SHORTCUTS_PREVIOUS).value
        enabled: CurrentPlayer.canGoPrevious && CurrentPlayer.active

        onTriggered: CurrentPlayer.previous()
    }
    property Action playPause: Action {
        shortcut: App.settings.get(SettingKey.SHORTCUTS_PLAY).value
        enabled: !CurrentPlayer.isStopped || CurrentPlayer.active

        onTriggered: CurrentPlayer.togglePlayPause()
    }
    property Action skipToNextSong: Action {
        shortcut: App.settings.get(SettingKey.SHORTCUTS_NEXT).value
        enabled: CurrentPlayer.canGoNext && CurrentPlayer.active

        onTriggered: CurrentPlayer.next()
    }

    // Other actions
    property Action toggleNotifications: Action {
        property var setting: App.settings.get(SettingKey.NOTIFICATIONS_ENABLED)

        checkable: true
        checked: setting.value
        shortcut: App.settings.get(SettingKey.SHORTCUTS_NOTIFICATIONS).value

        onToggled: setting.value = checked
    }
}
