import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs

ToolBar {
    id: root

    property bool atLeastOneServiceRunning: MainWindowViewModel.runningServices.model.count > 0

    spacing: 0

    Material.primary: ThemeViewModel.primary
    Material.foreground: ThemeViewModel.primaryForeground
    Material.theme: ThemeViewModel.isDark(ThemeViewModel.primary) ? Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent
        spacing: 0

        IconToolButton {
            action: Actions.toggleSelectServiceDrawer
            iconChar: MaterialIcons.icon_queue_music
            iconSize: 24
            tooltip: qsTr("Select another service")
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
                    action: Actions.toggleListeningHistory
                    iconChar: MaterialIcons.icon_history
                    tooltip: qsTr("Open listening history")
                }

                IconToolButton {
                    action: Actions.toggleNotifications
                    iconChar: checked ? MaterialIcons.icon_notifications_active : MaterialIcons.icon_notifications_off
                    tooltip: checked ? qsTr("Disable notifications") : qsTr("Enable notifications")
                    Material.accent: ThemeViewModel.accent === ThemeViewModel.primary ? ThemeViewModel.primaryForeground : ThemeViewModel.accent
                }

                PlayerToolBar { Layout.fillWidth: true; Layout.fillHeight: true }
            }
        }



        IconToolButton {
            id: menuButton

            iconChar: MaterialIcons.icon_more_vert
            iconSize: 24
            tooltip:  qsTr("Main menu")

            onTriggered: {
                if (menu.visible)
                    menu.close()
                else
                    menu.open()
            }
        }
    }

    MainMenu {
        id: menu

        y: implicitHeight > ApplicationWindow.window.contentItem.height ? 0 : parent.height + 3
        x: parent.width - implicitWidth - 3
    }
}
