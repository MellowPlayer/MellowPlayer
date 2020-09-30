import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

ToolBar {
    id: updateToolBar

    height: 0
    transform: Scale {
        id: scaleTransform

        origin.x: 0
        origin.y: updateToolBar.height
        xScale: 1
        yScale: 0
    }

    Material.background: ActiveTheme.secondary
    Material.foreground: ActiveTheme.secondaryForeground
    Material.accent: ActiveTheme.accent
    Material.theme: ActiveTheme.isDark(ActiveTheme.secondary) ?  Material.Dark : Material.Light

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            spacing: 8

            Item {
                width: 4
            }

            Label {
                text: MaterialIcons.icon_update
                font {
                    family: MaterialIcons.family
                    pixelSize: 26
                }
            }

            Label {
                text: Updater.status
                font.pixelSize: 14
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: qsTr("See release notes")
                onClicked: Qt.openUrlExternally(Updater.url + "/view/release#release")
            }

            ToolButton {
                highlighted: true
                text: qsTr("Install")
                enabled: !Updater.busy
                onClicked: Updater.install()
                visible: Updater.installEnabled
            }

            ToolButton {
                highlighted: true
                text: qsTr("Restart")
                onClicked: Updater.restart()
                visible: Updater.restartEnabled
            }

            ToolButton {
                hoverEnabled: true
                text: MaterialIcons.icon_close
                font {
                    family: MaterialIcons.family
                    pixelSize: 24
                }
                onClicked: Updater.close()
            }
        }

        ProgressBar {
            indeterminate: Updater.progress === -1
            from: 0; to: 100
            value: Updater.progress
            visible: Updater.busy

            Layout.fillWidth: true
        }
    }

    states: [
        State {
            when: Updater.visible

            PropertyChanges {
                target: updateToolBar
                height: updateToolBar.implicitHeight
            }

            PropertyChanges {
                target: scaleTransform
                yScale: 1
            }
        },
        State {
            when: !Updater.visible

            PropertyChanges {
                target: updateToolBar
                height: 0
            }

            PropertyChanges {
                target: scaleTransform
                yScale: 0
            }
        }
    ]
    transitions: Transition {
        from: "*"; to: "*"; reversible: true

        PropertyAnimation {
            properties: "yScale, height"
            duration: 200
        }
    }
}
