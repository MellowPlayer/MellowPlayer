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
            hoverEnabled: true
            text: qsTr("Clear cookies")
            onClicked: {
                paneRestart.state = "visible"
                App.clearCookies();
            }

            Layout.fillWidth: true
        }

        Rectangle {
            color: ActiveTheme.isDark(ActiveTheme.background) ? Qt.lighter(ActiveTheme.background) : Qt.darker(ActiveTheme.background, 1.1)
            height: 1
            Layout.fillWidth: true
        }

        ToolButton {
            highlighted: true
            hoverEnabled: true
            text: qsTr("Clear cache")
            onClicked: {
                paneRestart.state = "visible"
                App.clearCache();
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

        Material.background: ActiveTheme.primary
        Material.elevation: 8
        Material.foreground: ActiveTheme.primaryForeground
        Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

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
                onClicked: App.restart()
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
