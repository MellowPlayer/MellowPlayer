import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs

ToolBar {
    id: root

    property bool atLeastOneServiceRunning: MainWindow.runningServices.model.count > 0

    spacing: 0

    Material.primary: ActiveTheme.primary
    Material.foreground: ActiveTheme.primaryForeground
    Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent
        spacing: 0

        IconToolButton {
            action: Actions.toggleCurrentPage
            iconChar: MainWindow.isOnRunningServicesPage ? MaterialIcons.icon_apps : MaterialIcons.icon_keyboard_arrow_left
            iconSize: 24
            tooltip: MainWindow.isOnRunningServicesPage
                    ? qsTr("Select another service")
                    : root.atLeastOneServiceRunning
                        ? qsTr("Go back to ") + StreamingServices.currentServiceName
                        : ""
            visible: MainWindow.runningServices.model.count > 0
        }

        Item {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent
                layoutDirection: "RightToLeft"
                spacing: 0

                IconToolButton {
                    action: Actions.openListeningHistory
                    iconChar: MaterialIcons.icon_history
                    tooltip: qsTr("Open listening history")
                    shortcut: App.settings.get(SettingKey.SHORTCUTS_LISTENING_HISTORY).value
                }

                IconToolButton {
                    action: Actions.toggleNotifications
                    iconChar: checked ? MaterialIcons.icon_notifications_active : MaterialIcons.icon_notifications_off
                    tooltip: checked ? qsTr("Disable notifications") : qsTr("Enable notifications")
                    Material.accent: ActiveTheme.accent === ActiveTheme.primary ? ActiveTheme.primaryForeground : ActiveTheme.accent
                }

                PlayerToolBar { Layout.fillWidth: true; Layout.fillHeight: true }
                WebViewToolBar { Layout.fillHeight: true }
            }
        }



        IconToolButton {
            id: menuButton

            iconChar: MaterialIcons.icon_more_vert
            iconSize: 24
            tooltip:  qsTr("Main menu")

            onTriggered: menu.open()
        }
    }

    MainMenu {
        id: menu

        y: parent.height + 3
        x: parent.width - implicitWidth - 3
    }

    Label {
        anchors.centerIn: parent
        text: qsTr("Which streaming service would you like to use?")
        font.pixelSize: 14
        visible: !MainWindow.isOnRunningServicesPage
    }
}
