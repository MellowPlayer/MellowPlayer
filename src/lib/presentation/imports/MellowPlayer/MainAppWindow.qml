import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0
import "Dialogs.js" as Dialogs

ApplicationWindow {
    id: root


    minimumWidth: 450
    minimumHeight: 450
    width: App.settings.get(SettingKey.PRIVATE_WINDOW_WIDTH).value;
    height: App.settings.get(SettingKey.PRIVATE_WINDOW_HEIGHT).value;
    title: StreamingServices.currentService !== null ? StreamingServices.currentServiceName : ""

    onClosing: d.handleCloseEvent(close);

    Component.onCompleted: {
        Dialogs.initialize(root);
        MainWindow.quitRequest.connect(() => { d.quit(); });
        MainWindow.forceQuitRequest.connect(() => { d.forceQuit = true; App.quit(); });
        MainWindow.raiseRequested.connect(() => { d.restoreWindow(); });
    }
    Material.accent: ActiveTheme.accent
    Material.background: ActiveTheme.background
    Material.foreground: ActiveTheme.foreground
    Material.primary: ActiveTheme.primary
    Material.theme: ActiveTheme.dark ? Material.Dark : Material.Light

    header: MainToolBar {
        id: mainToolBar

        visible: App.settings.get(SettingKey.APPEARANCE_TOOLBAR_VISIBLE).value && !MainWindow.fullScreen
    }

    footer: UpdateToolBar { }

    RunningServicesPage {
        id: runningServicesPage
        anchors.fill: parent
    }

    SelectServiceDrawer {
        id: selectServiceDrawer

        height: root.height; width: 450
    }

    SettingsDrawer {
        id: settingsDrawer;

        width: root.width; height: root.height
    }

    ListeningHistoryDrawer {
        id: listeningHistoryDrawer;

        height: root.height; width: 450
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
        shortcut: App.settings.get(SettingKey.SHORTCUTS_SELECT_SERVICE).value
        onTriggered: {
            if (selectServiceDrawer.visible) {
                console.log("Closing service selection drawer")
                selectServiceDrawer.close()
            } else {
                console.log("Opening service selection drawer")
                runningServicesPage.updateImages();
                selectServiceDrawer.open();
            }
        }
        Component.onCompleted: Actions.toggleSelectServiceDrawer = toggleSelectServiceDrawerAction
    }

    Action {
        id: toggleListeningHistoryAction
        shortcut: App.settings.get(SettingKey.SHORTCUTS_LISTENING_HISTORY).value
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
        shortcut: App.settings.get(SettingKey.SHORTCUTS_SETTINGS).value
        text: qsTr("Settings")
        onTriggered: settingsDrawer.open()
        Component.onCompleted: Actions.openSettings = openSettingsAction
    }

    Action {
        id: createNewPluginAction
        shortcut: App.settings.get(SettingKey.SHORTCUTS_CREATE_PLUGIN).value
        text: qsTr("Create plugin")
        onTriggered: newPluginWizard.open()
        Component.onCompleted: Actions.createNewPlugin = createNewPluginAction
    }

    Action {
        id: reportIssueAction
        shortcut: App.settings.get(SettingKey.SHORTCUTS_REPORT_ISSUE).value
        text: qsTr("Report issue")
        onTriggered: Dialogs.reportIssue()
        Component.onCompleted: Actions.reportIssue = reportIssueAction
    }

    Action {
        id: toggleToolBarAction
        shortcut: App.settings.get(SettingKey.SHORTCUTS_SHOW_TOOLBAR).value
        text: qsTr("Toggle main toolbar")
        onTriggered: App.settings.get(SettingKey.APPEARANCE_TOOLBAR_VISIBLE).value = !App.settings.get(SettingKey.APPEARANCE_TOOLBAR_VISIBLE).value
        Component.onCompleted: Actions.toggleToolBar = toggleToolBarAction
    }

    Action {
        id: checkForUpdatesAction
        enabled: !Updater.busy
        shortcut: App.settings.get(SettingKey.SHORTCUTS_CHECK_FOR_UPDATE).valu
        text: qsTr("Check for update")
        onTriggered: Updater.check()
        Component.onCompleted: Actions.checkForUpdates = checkForUpdatesAction
    }

    Action {
        id: showAboutAction
        shortcut: App.settings.get(SettingKey.SHORTCUTS_ABOUT).value
        text: qsTr("About")
        onTriggered: Dialogs.showAbout()
        Component.onCompleted: Actions.showAbout = showAboutAction
    }

    Action {
        id: quitAction
        shortcut: App.settings.get(SettingKey.SHORTCUTS_QUIT).value
        text: qsTr("Quit")
        onTriggered: MainWindow.requestQuit()
        Component.onCompleted: Actions.quit = quitAction
    }


    QtObject {
        id: d

        property bool forceQuit: false;
        property bool fullScreen: MainWindow.fullScreen
        property bool visible: MainWindow.visible

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
            root.visible = true;
            root.raise();
            root.requestActivate();
        }

        function saveGeometry() {
            App.settings.get(SettingKey.PRIVATE_WINDOW_WIDTH).value = root.width;
            App.settings.get(SettingKey.PRIVATE_WINDOW_HEIGHT).value = root.height;
        }

        function handleCloseEvent(close) {
            saveGeometry();
            var closeToTray = App.settings.get(SettingKey.MAIN_CLOSE_TO_TRAY).value
            if (closeToTray && !forceQuit) {
                var showMessageSetting = App.settings.get(SettingKey.PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE)
                if (showMessageSetting.value) {
                    showMessageSetting.value = false;
                    Dialogs.showMessage(
                        qsTr("Closing to system tray"),
                        qsTr("<p>MellowPlayer will continue to run in background.<br>You can quit the application or restore the main window via the system tray icon menu.</p>"),
                        (confirmed) => {
                            if (confirmed) {
                                MainWindow.visible = false;
                            }
                        }
                    );
                }
                else {
                    MainWindow.visible = false;
                }
                close.accepted = false;
            }
        }

        function quit() {
            saveGeometry();
            var confirmExit = App.settings.get(SettingKey.MAIN_CONFIRM_EXIT).value;
            if (confirmExit) {
                d.restoreWindow();
                Dialogs.askConfirmation(
                    qsTr("Confirm quit"),
                    qsTr("Are you sure you want to quit MellowPlayer?"),
                    (confirmed) => {
                        if (confirmed) {
                            console.log("quit")
                            App.quit()
                        }
                    }
                )
            }
            else {
                App.quit();
            }
        }
    }
}
