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

    Material.background: _theme.secondary
    Material.foreground: _theme.secondaryForeground
    Material.accent: _theme.accent
    Material.theme: _theme.isDark(_theme.secondary) ?  Material.Dark : Material.Light

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
                text: _updater.status
                font.pixelSize: 16
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: qsTr("See release notes")
                onClicked: Qt.openUrlExternally(_updater.url + "/view/release#release")
            }

            ToolButton {
                highlighted: true
                text: qsTr("Install")
                enabled: !_updater.busy
                onClicked: _updater.install()
                visible: _updater.installEnabled
            }

            ToolButton {
                highlighted: true
                text: qsTr("Restart")
                onClicked: _updater.restart()
                visible: _updater.restartEnabled
            }

            ToolButton {
                hoverEnabled: true
                text: MaterialIcons.icon_close
                font {
                    family: MaterialIcons.family
                    pixelSize: 24
                }
                onClicked: _updater.close()
            }
        }

        ProgressBar {
            indeterminate: _updater.progress === -1
            from: 0; to: 100
            value: _updater.progress
            visible: _updater.busy

            Layout.fillWidth: true
        }
    }

    states: [
        State {
            when: _updater.visible

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
            when: !_updater.visible

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
