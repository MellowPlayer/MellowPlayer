import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0
import "Dialogs.js" as Dialogs

ApplicationWindow {
    id: root


    minimumWidth: 360; minimumHeight: 360
    width: SettingsViewModel.get(SettingKey.PRIVATE_WINDOW_WIDTH).value;
    height: SettingsViewModel.get(SettingKey.PRIVATE_WINDOW_HEIGHT).value;

    title: {
        var currentSong = CurrentPlayer.currentSong;
        if (currentSong.title && currentSong.artist)
            return qsTr("%1 by %2").arg(currentSong.title).arg(currentSong.artist);
        else if (currentSong.title)
            return currentSong.title;
        return StreamingServicesViewModel.currentService !== null ? StreamingServicesViewModel.currentServiceName : "";
    }
    visible: MainWindowViewModel.visible

    onClosing: d.handleCloseEvent(close)

    Component.onCompleted: {
        Dialogs.initialize(root);
        MainWindowViewModel.quitRequest.connect(() => { d.quit(); });
        MainWindowViewModel.forceQuitRequest.connect(() => { d.forceQuit = true; ApplicationViewModel.quit(); });
        MainWindowViewModel.raiseRequested.connect(() => { d.restoreWindow(); });
    }
    Material.accent: ThemeViewModel.accent
    Material.background: ThemeViewModel.background
    Material.foreground: ThemeViewModel.foreground
    Material.primary: ThemeViewModel.primary
    Material.theme: ThemeViewModel.dark ? Material.Dark : Material.Light

    header: MainToolBar {
        id: mainToolBar

        visible: SettingsViewModel.get(SettingKey.APPEARANCE_TOOLBAR_VISIBLE).value && !MainWindowViewModel.fullScreen
    }

    footer: ColumnLayout {
        spacing: 0

        PlayerFooter {
            id: playerFooter

            drawer: playerDrawer
            visible: MainWindowViewModel.runningServices.model.count > 0 &&
                     SettingsViewModel.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value &&
                     ApplicationWindow.window.width <= 767

            Layout.fillWidth: true
            Layout.preferredHeight: height
        }

        UpdateToolBar {
            Layout.fillWidth: true
            Layout.preferredHeight: height
        }
    }

    RunningServicesPage {
        id: runningServicesPage
        anchors.fill: parent
    }

    SelectServiceDrawer {
        id: selectServiceDrawer

        height: root.height
        width: root.width >= 450 ? 450 : root.width
    }

    SettingsDrawer {
        id: settingsDrawer;

        width: root.width; height: root.height
    }

    ListeningHistoryDrawer {
        id: listeningHistoryDrawer;

        height: root.height
        width: root.width >= 450 ? 450 : root.width
    }

    PlayerDrawer {
        id: playerDrawer
    }

    NewPluginWizard {
        id: newPluginWizard

        property real scaleFactor: 0.9

        modal: true
        width: 450; height: 450
        x: root.width / 2 - width / 2;
        y: root.height / 2 - height / 2 - 48;
    }

    FullScreenNotification {
        id: fullScreenNotification

        x: (root.width - width) / 2
        y: 12
        visible: false
    }

    Action {
        id: toggleSelectServiceDrawerAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_SELECT_SERVICE).value
        onTriggered: {
            if (selectServiceDrawer.visible) {
                console.log("Closing service selection drawer")
                selectServiceDrawer.close()
            } else {
                console.log("Opening service selection drawer")
                selectServiceDrawer.open();
            }
        }
        Component.onCompleted: Actions.toggleSelectServiceDrawer = toggleSelectServiceDrawerAction
    }

    Action {
        id: toggleListeningHistoryAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_LISTENING_HISTORY).value
        onTriggered: {
            if (listeningHistoryDrawer.visible) {
                console.log("Closing listening history drawer")
                listeningHistoryDrawer.close()
            } else {
                console.log("Opening listening history drawer")
                listeningHistoryDrawer.open()
            }
        }
        Component.onCompleted: Actions.toggleListeningHistory = toggleListeningHistoryAction
    }

    Action {
        id: openSettingsAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_SETTINGS).value
        text: qsTr("Settings")
        onTriggered: settingsDrawer.open()
        Component.onCompleted: Actions.openSettings = openSettingsAction
    }

    Action {
        id: createNewPluginAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_CREATE_PLUGIN).value
        text: qsTr("Create plugin")
        onTriggered: newPluginWizard.open()
        Component.onCompleted: Actions.createNewPlugin = createNewPluginAction
    }

    Action {
        id: reportIssueAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_REPORT_ISSUE).value
        text: qsTr("Report issue")
        onTriggered: Dialogs.reportIssue()
        Component.onCompleted: Actions.reportIssue = reportIssueAction
    }

    Action {
        id: toggleToolBarAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_SHOW_TOOLBAR).value
        text: qsTr("Toggle main toolbar")
        onTriggered: SettingsViewModel.get(SettingKey.APPEARANCE_TOOLBAR_VISIBLE).value = !SettingsViewModel.get(SettingKey.APPEARANCE_TOOLBAR_VISIBLE).value
        Component.onCompleted: Actions.toggleToolBar = toggleToolBarAction
    }

    Action {
        id: showDevtoolsAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_SHOW_DEVTOOLS).value
        text: qsTr("Open web developer tools")
        onTriggered: DevToolsWindowViewModel.show()
        Component.onCompleted: Actions.showDevtools = showDevtoolsAction
    }

    Action {
        id: checkForUpdatesAction
        enabled: !UpdaterViewModel.busy
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_CHECK_FOR_UPDATE).valu
        text: qsTr("Check for update")
        onTriggered: UpdaterViewModel.check()
        Component.onCompleted: Actions.checkForUpdates = checkForUpdatesAction
    }

    Action {
        id: showAboutAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_ABOUT).value
        text: qsTr("About")
        onTriggered: Dialogs.showAbout()
        Component.onCompleted: Actions.showAbout = showAboutAction
    }

    Action {
        id: quitAction
        shortcut: SettingsViewModel.get(SettingKey.SHORTCUTS_QUIT).value
        text: qsTr("Quit")
        onTriggered: MainWindowViewModel.requestQuit()
        Component.onCompleted: Actions.quit = quitAction
    }

    Action {
        id: zenModeAction
        enabled: StreamingServicesViewModel.currentService !== null
        text: qsTr("Zen Mode")
        onTriggered: playerDrawer.open()

        Component.onCompleted: Actions.zenMode = zenModeAction
    }

    QtObject {
        id: d

        property bool forceQuit: false;
        property bool fullScreen: MainWindowViewModel.fullScreen
        property bool visible: MainWindowViewModel.visible

        onVisibleChanged: {
            if (visible) {
                d.restoreWindow();
            } else {
                d.hideWindow()
            }
        }

        onFullScreenChanged: {
            if (fullScreen) {
                root.showFullScreen();
                fullScreenNotification.visible = true;
            }
            else {
                root.showNormal();
            }
        }

        function hideWindow() {
            root.hide();
        }

        function restoreWindow() {
            MainWindowViewModel.visible = true;
            root.raise();
            root.requestActivate();
        }

        function saveGeometry() {
            SettingsViewModel.get(SettingKey.PRIVATE_WINDOW_WIDTH).value = root.width;
            SettingsViewModel.get(SettingKey.PRIVATE_WINDOW_HEIGHT).value = root.height;
        }

        function handleCloseEvent(close) {
            saveGeometry();
            var closeToTray = SettingsViewModel.get(SettingKey.MAIN_CLOSE_TO_TRAY).value
            if (closeToTray && !forceQuit) {
                var showMessageSetting = SettingsViewModel.get(SettingKey.PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE)
                if (showMessageSetting.value) {
                    showMessageSetting.value = false;
                    Dialogs.showMessage(
                        qsTr("Closing to system tray"),
                        qsTr("<p>MellowPlayer will continue to run in background.<br>You can quit the application or restore the main window via the system tray icon menu.</p>"),
                        (confirmed) => {
                            if (confirmed) {
                                MainWindowViewModel.visible = false;
                            }
                        }
                    );
                }
                else {
                    console.error("Hiding window", MainWindowViewModel.visible)
                    MainWindowViewModel.visible = false;
                }
                close.accepted = false;
            }
        }

        function quit() {
            saveGeometry();
            var confirmExit = SettingsViewModel.get(SettingKey.MAIN_CONFIRM_EXIT).value;
            if (confirmExit) {
                d.restoreWindow();
                Dialogs.askConfirmation(
                    qsTr("Confirm quit"),
                    qsTr("Are you sure you want to quit MellowPlayer?"),
                    (confirmed) => {
                        if (confirmed) {
                            console.log("quit")
                            ApplicationViewModel.quit()
                        }
                    }
                )
            }
            else {
                ApplicationViewModel.quit();
            }
        }
    }
}
