import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

ToolBar {
    id: root

    property bool searchEnabled: true
    property alias searchChecked: btSearch.checked

    signal quitRequested()

    Material.primary: ThemeViewModel.primary
    Material.foreground: ThemeViewModel.primaryForeground
    Material.elevation: 4
    Material.theme: ThemeViewModel.isDark(ThemeViewModel.primary) ? Material.Dark : Material.Light

    RowLayout {
        anchors.fill: parent

        ToolButton {
            id: btSearch

            checkable: true
            checked: false
            font { family: MaterialIcons.family; pixelSize: 22 }
            text: MaterialIcons.icon_search

            hoverEnabled: true
            enabled: root.enabled

            Material.accent: ThemeViewModel.accent === ThemeViewModel.primary ? ThemeViewModel.primaryForeground : ThemeViewModel.accent

            Tooltip {
                text: qsTr("Search/filter")
            }
        }

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            id: btBackFromListeningHistory

            font { family: MaterialIcons.family; pixelSize: 22 }
            hoverEnabled: true
            action: Actions.toggleListeningHistory
            text: MaterialIcons.icon_keyboard_arrow_right

            Layout.fillHeight: true

            Tooltip {
                text: qsTr("Back")
            }
        }
    }

    Label {
        anchors.centerIn: parent
        text: qsTr("Listening history")
    }
}
