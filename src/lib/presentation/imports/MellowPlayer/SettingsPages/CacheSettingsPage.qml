import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Item {
    clip: true

    ColumnLayout {
        anchors.fill: parent
        clip: true
        spacing: 0

        ToolButton{
            highlighted: true
            hoverEnabled: !ApplicationViewModel.hasTouchScreen
            text: qsTr("Clear cookies")
            onClicked: {
                paneRestart.state = "visible"
                ApplicationViewModel.clearCookies();
            }

            Layout.fillWidth: true
        }

        Rectangle {
            color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
            height: 1
            Layout.fillWidth: true
        }

        ToolButton {
            highlighted: true
            hoverEnabled: !ApplicationViewModel.hasTouchScreen
            text: qsTr("Clear cache")
            onClicked: {
                paneRestart.state = "visible"
                ApplicationViewModel.clearCache();
            }

            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
        }
    }


    Pane {
        id: paneRestart

        clip: true
        width: parent.width

        Material.background: ThemeViewModel.primary
        Material.elevation: 8
        Material.foreground: ThemeViewModel.primaryForeground
        Material.theme: ThemeViewModel.isDark(ThemeViewModel.primary) ? Material.Dark : Material.Light

        RowLayout {
            id: rowLayout
            anchors.fill: parent
            spacing: 8

            Label {
                text: MaterialIcons.icon_info
                font {
                    family: MaterialIcons.family
                    pixelSize: 32
                }
            }

            Label {
                text: qsTr("You need to restart MellowPlayer for the change to be applied.")
                font.pixelSize: 14
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: qsTr("Restart now")
                onClicked: ApplicationViewModel.restart()
            }
        }

        state: "hidden"
        states: [
            State {
                name: "hidden"

                PropertyChanges { target: paneRestart; y: paneRestart.parent.height }
            },

            State {
                name: "visible"

                PropertyChanges { target: paneRestart; y: paneRestart.parent.height - paneRestart.implicitHeight }
            }
        ]
        transitions: Transition {
            from: "hidden"
            to: "visible"

            PropertyAnimation { properties: "y" }
        }
    }
}
