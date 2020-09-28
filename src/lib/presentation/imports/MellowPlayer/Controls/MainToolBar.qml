import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

ToolBar {
    id: root

    property bool isCurrentServiceRunning: false

    Material.primary: ActiveTheme.primary
    Material.foreground: ActiveTheme.primaryForeground
    Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent
        spacing: 0

        IconToolButton {
            iconChar: mainWindow.isOnRunningServicesPage ? MaterialIcons.icon_apps : MaterialIcons.icon_keyboard_arrow_left
            tooltip: mainWindow.isOnRunningServicesPage ?
                         qsTr("Select another service") :
                         mainWindow.hasRunningServices ? qsTr("Go back to ") + StreamingServices.currentService.name : ""
            visible: mainWindow.hasRunningServices

            onClicked: {
                if (!mainWindow.isOnRunningServicesPage && mainWindow.hasRunningServices)
                    stack.slideTransitions = true;
                else
                    stack.slideTransitions = false;
                mainWindow.toggleActivePage();
            }
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_WEBPAGE_CONTROLS_VISIBLE).value

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_chevron_left
            tooltip: qsTr("Go back")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_WEBPAGE_CONTROLS_VISIBLE).value

            onTriggered: mainWindow.runningServices.goBack()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_chevron_right
            tooltip: qsTr("Go forward")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_WEBPAGE_CONTROLS_VISIBLE).value

            onTriggered: mainWindow.runningServices.goForward()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_refresh
            tooltip: qsTr("Reload page")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_WEBPAGE_CONTROLS_VISIBLE).value
            shortcut: App.settings.get(SettingKey.SHORTCUTS_RELOAD).value

            onTriggered: mainWindow.runningServices.reload()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_home
            tooltip: qsTr("Go to home page")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_WEBPAGE_CONTROLS_VISIBLE).value

            onTriggered: mainWindow.runningServices.goHome()
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            visible:  mainWindow.isOnRunningServicesPage && CurrentPlayer.canAddToFavorites && App.settings.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }
        }

        IconToolButton {
            visible: mainWindow.isOnRunningServicesPage && CurrentPlayer.canAddToFavorites && App.settings.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value
            iconChar: CurrentPlayer.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border
            tooltip: CurrentPlayer.currentSong.isFavorite ? qsTr("Remove current song from your favorites") : qsTr("Add current song to your favorites")
            shortcut: App.settings.get(SettingKey.SHORTCUTS_FAVORITE).value

            onTriggered: CurrentPlayer.toggleFavoriteSong()
        }

        Item {
            Layout.fillWidth: true
        }

        IconToolButton {
            enabled: CurrentPlayer.canGoPrevious && d.isPlayerActive()
            iconChar: MaterialIcons.icon_fast_rewind
            tooltip: qsTr("Skip to previous song")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value
            shortcut: App.settings.get(SettingKey.SHORTCUTS_PREVIOUS).value

            onTriggered: CurrentPlayer.previous()
        }

        IconToolButton {
            enabled: !CurrentPlayer.isStopped || d.isPlayerActive()
            iconChar: CurrentPlayer.isPlaying ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
            tooltip: CurrentPlayer.isPlaying ? qsTr("Pause") : qsTr("Play")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value
            shortcut: App.settings.get(SettingKey.SHORTCUTS_PLAY).value

            onTriggered: CurrentPlayer.togglePlayPause()
        }

        IconToolButton {
            enabled: CurrentPlayer.canGoNext && d.isPlayerActive()
            iconChar: MaterialIcons.icon_fast_forward
            tooltip: qsTr("Skip to next song")
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value
            shortcut: App.settings.get(SettingKey.SHORTCUTS_NEXT).value

            onTriggered: CurrentPlayer.next()
        }

        IconToolButton {
            property var setting: App.settings.get(SettingKey.NOTIFICATIONS_ENABLED)

            checkable: true
            checked: setting.value
            iconChar: checked ? MaterialIcons.icon_notifications_active : MaterialIcons.icon_notifications_off
            tooltip: checked ? qsTr("Disable notifications") : qsTr("Enable notifications")
            shortcut: App.settings.get(SettingKey.SHORTCUTS_NOTIFICATIONS).value

            onCheckedChanged: setting.value = checked;
            onTriggered: checked = !checked;

            Material.accent: ActiveTheme.accent === ActiveTheme.primary ? ActiveTheme.primaryForeground : ActiveTheme.accent
        }

        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true

            Rectangle {
                anchors.centerIn: parent
                width: 1
                height: parent.height * 0.33
                color: Material.color(Material.Grey)
            }

            visible: mainWindow.isOnRunningServicesPage
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_history
            tooltip: qsTr("Open listening history")
            shortcut: App.settings.get(SettingKey.SHORTCUTS_LISTENING_HISTORY).value

            onTriggered: listeningHistoryDrawer.open()
        }

        IconToolButton {
            iconChar: MaterialIcons.icon_more_vert
            tooltip:  qsTr("Main menu")

            onTriggered: menu.open()

            Shortcut {
                id: shortcutSettings

                sequence: App.settings.get(SettingKey.SHORTCUTS_SETTINGS).value

                onActivated: settingsDrawer.open()
            }

            Shortcut {
                id: shortcutCreatePlugin

                sequence: App.settings.get(SettingKey.SHORTCUTS_CREATE_PLUGIN).value

                onActivated: newPluginWizard.open()
            }

            Shortcut {
                id: shortcutReportIssue

                sequence: App.settings.get(SettingKey.SHORTCUTS_REPORT_ISSUE).value

                onActivated: reportIssueDialog.open()
            }


            Shortcut {
                id: shortcutCheckForUpdates

                enabled: !Updater.busy
                sequence: App.settings.get(SettingKey.SHORTCUTS_CHECK_FOR_UPDATE).value

                onActivated: Updater.check()
            }

            Shortcut {
                id: shortcutAbout

                sequence: App.settings.get(SettingKey.SHORTCUTS_ABOUT).value

                onActivated: aboutDialog.open()
            }

            Shortcut {
                id: shortcutQuit

                sequence: App.settings.get(SettingKey.SHORTCUTS_QUIT).value

                onActivated: MainWindow.requestQuit()
            }

            Menu {
                id: menu
                y: parent.implicitHeight
                width: zoomMenuItem.width
                spacing: 0

                IconMenuItem {
                    id: menuItemSettings

                    iconChar: MaterialIcons.icon_settings
                    shortcut: shortcutSettings.sequence
                    text: qsTr("Settings")

                    onClicked: settingsDrawer.open()
                }

                MenuItem {
                    id: zoomMenuItem
                    hoverEnabled: true
                    padding: 0
                    spacing: 0


                    background: ColumnLayout {
                        MenuSeparator { Layout.fillWidth: true }
                        Item { Layout.fillHeight: true }
                        MenuSeparator { Layout.fillWidth: true }
                    }

                    contentItem: RowLayout {
                        spacing: 0

                        Label {
                            text: qsTr("Zoom")

                            Layout.leftMargin: 16
                        }

                        ToolSeparator { Layout.fillHeight: true }

                        SpinBox {
                            id: zoomSpinBox

                            padding: 0

                            from: 50
                            to: 300
                            stepSize: 25
                            value: MainWindow.zoom.value * 100

                            onValueChanged: MainWindow.zoom.value = value / 100.0

                            textFromValue:  function(value, locale) {
                                return Number(value).toLocaleString(locale, 'f', 0) + "%";
                            }
                        }

                        ToolSeparator { Layout.fillHeight: true }

                        Button {
                            id: zoomResetButton

                            text: MaterialIcons.icon_fullscreen
                            font.family: MaterialIcons.family
                            font.pixelSize: 22
                            implicitWidth: 48
                            flat: true

                            onClicked: MainWindow.zoom.reset()

                            Layout.rightMargin: 16
                        }
                    }
                }

                IconMenuItem {
                    id: menuCreatePlugin

                    iconChar: MaterialIcons.icon_extension
                    shortcut: shortcutCreatePlugin.sequence
                    text: qsTr("Create plugin")

                    onClicked: newPluginWizard.open()
                }

                IconMenuItem {
                    id: menuReportIssue

                    iconChar: MaterialIcons.icon_bug_report
                    shortcut: shortcutReportIssue.sequence
                    text: qsTr("Report issue")

                    onClicked: reportIssueDialog.open()
                }

                IconMenuItem {
                    iconChar: MaterialIcons.icon_update
                    text: qsTr("Check for update")
                    enabled: !Updater.busy
                    shortcut: shortcutCheckForUpdates.sequence

                    onClicked: Updater.check()

                    ProgressBar {
                        anchors{ bottom: parent.bottom; horizontalCenter: parent.left; right: parent.right }
                        indeterminate: Updater.progress === -1
                        from: 0; to: 100
                        value: Updater.progress
                        visible: Updater.busy
                    }
                }

                MenuSeparator { }

                IconMenuItem {
                    id: menuItemAbout

                    iconChar: MaterialIcons.icon_info_outline
                    shortcut: shortcutAbout.sequence
                    text: qsTr("About")

                    onClicked: aboutDialog.open()
                }

                IconMenuItem {
                    iconChar: MaterialIcons.icon_power_settings_new
                    shortcut: shortcutQuit.sequence
                    text: qsTr("Quit")

                    onClicked: MainWindow.requestQuit()
                }
            }
        }
    }

    Item {
        id: centerItem
        anchors.centerIn: parent
        height: root.height
        width: 500

        Label {
            anchors.centerIn: parent
            text: qsTr("Which streaming service would you like to use?")
            font.pixelSize: 16
            visible: !songInfoItem.visible
        }

        ColumnLayout {
            id: songInfoItem

            anchors.fill: parent
            anchors.margins: 9
            spacing: 0
            visible: mainWindow.isOnRunningServicesPage && App.settings.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value

            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: getText()
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: sliderGroup.visible ? "AlignTop" : "AlignVCenter"
                elide: "ElideMiddle"
                font.pixelSize: sliderGroup.visible ? 12 : 14

                function getText() {
                    var currentSong = CurrentPlayer.currentSong;
                    if (currentSong.title && currentSong.artist)
                        return "<b>" + currentSong.title + qsTr("</b><i> by ") + currentSong.artist;
                    else if (currentSong.title)
                        return "<b>" + currentSong.title + "</b>";
                    else if (StreamingServices.currentService !== null)
                        return StreamingServices.currentService.name;
                    return "";
                }
            }

            Item {
                id: sliderGroup

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: layout.implicitWidth
                Layout.preferredHeight: visible ? slider.implicitHeight : 0
                Layout.margins: 0

                visible: CurrentPlayer.canSeek || CurrentPlayer.currentSong.duration !== 0

                RowLayout {
                    id: layout

                    anchors.fill: parent

                    Label {
                        text: {
                            var date = new Date(null);
                            date.setSeconds(CurrentPlayer.position); // specify value for SECONDS here
                            var text = date.toISOString().substr(11, 8);
                            try {
                                if (text.startsWith("00:"))
                                    text = text.substr(3);
                            }
                            catch (TypeError) {

                            }
                            return text;
                        }
                        font.pixelSize: 11
                    }

                    Slider {
                        id: slider

                        function updateHandleVisibility() {
                            slider.handle.visible = CurrentPlayer.canSeek
                        }

                        hoverEnabled: true
                        from: 0; to: CurrentPlayer.currentSong.duration
                        value: CurrentPlayer.position

                        onMoved: {
                            if (CurrentPlayer.position !== value && CurrentPlayer.position < CurrentPlayer.currentSong.duration)
                                CurrentPlayer.seekToPosition(value)
                        }

                        Component.onCompleted: slider.updateHandleVisibility()
                        Layout.fillWidth: true
                        Material.accent: ActiveTheme.accent === ActiveTheme.primary ? ActiveTheme.primaryForeground : ActiveTheme.accent

                        Connections {
                            target: CurrentPlayer

                            function onCanSeekChanged() { slider.updateHandleVisibility() }
                        }

                    }

                    Label {
                        text: {
                            var date = new Date(null);
                            date.setSeconds(CurrentPlayer.currentSong.duration - CurrentPlayer.position); // specify value for SECONDS here
                            var text = date.toISOString().substr(11, 8);
                            try {
                                if (text.startsWith("00:"))
                                    text = text.substr(3);
                            }
                            catch (TypeError) {

                            }
                            return "-" + text;
                        }
                        font.pixelSize: 11
                    }
                }
            }
        }
    }

    QtObject {
        id: d
        property int iconSize: 22

        function isPlayerActive() {
            return CurrentPlayer.currentSong !== null && CurrentPlayer.currentSong.isValid()
        }
    }

}
