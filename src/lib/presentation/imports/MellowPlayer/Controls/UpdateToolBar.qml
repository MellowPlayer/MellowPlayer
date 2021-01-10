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

    Material.background: ThemeViewModel.secondary
    Material.foreground: ThemeViewModel.secondaryForeground
    Material.accent: ThemeViewModel.accent
    Material.theme: ThemeViewModel.isDark(ThemeViewModel.secondary) ?  Material.Dark : Material.Light

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
                text: UpdaterViewModel.status
                font.pixelSize: 14
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: qsTr("See release notes")
                onClicked: Qt.openUrlExternally(UpdaterViewModel.url + "/view/release#release")
            }

            ToolButton {
                highlighted: true
                text: qsTr("Install")
                enabled: !UpdaterViewModel.busy
                onClicked: UpdaterViewModel.install()
                visible: UpdaterViewModel.installEnabled
            }

            ToolButton {
                highlighted: true
                text: qsTr("Restart")
                onClicked: UpdaterViewModel.restart()
                visible: UpdaterViewModel.restartEnabled
            }

            ToolButton {
                hoverEnabled: !ApplicationViewModel.hasTouchScreen
                text: MaterialIcons.icon_close
                font {
                    family: MaterialIcons.family
                    pixelSize: 24
                }
                onClicked: UpdaterViewModel.close()
            }
        }

        ProgressBar {
            indeterminate: UpdaterViewModel.progress === -1
            from: 0; to: 100
            value: UpdaterViewModel.progress
            visible: UpdaterViewModel.busy

            Layout.fillWidth: true
        }
    }

    states: [
        State {
            when: UpdaterViewModel.visible

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
            when: !UpdaterViewModel.visible

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
