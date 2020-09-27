import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10
import QtGraphicalEffects 1.0

import MellowPlayer 3.0

Item {
    id: root

    property int index: model.sortIndex
    property string backgroundColor: Material.background
    property bool hovered: mouseArea.containsMouse
    property var service: model.qtObject

    onIndexChanged: model.sortIndex = root.index
    Drag.active: mouseArea.drag.active

    Component.onCompleted: model.sortIndex = root.index

    Item {
        id: pane

        anchors.fill: parent
        anchors.margins: parent.width / 50

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: root.width
                height: root.height
                radius: 6
            }
        }

        Material.elevation: state == "hover" ? 8 : 4

        Item {
            anchors.fill: parent

            Image {
                id: preview

                property bool rounded: true
                property bool adapt: true

                anchors.fill: parent
                source: model.previewImageUrl
            }

            FastBlur {
                anchors.fill: preview
                source: preview
                radius: 32
            }

            ColorOverlay {
                id: overlay
                anchors.fill: preview
                source: preview
                color: "black"
                opacity: 0.3
            }

            state: root.hovered || starButton.hovered || stopButton.hovered ? "hover" : ""
            states: State {
                name: "hover"

                PropertyChanges {
                    target: overlay
                    opacity: 0.0

                }
            }
            transitions: [
                Transition {
                    PropertyAnimation { properties: "opacity" }
                }
            ]

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                y: parent.height / 5
                antialiasing: true
                height: 64; width: 64
                mipmap: true
                source: model.logo
            }
        }

        MouseArea {
            id: mouseArea

            anchors.fill: parent
            drag.target: item
            hoverEnabled: true
            propagateComposedEvents: true

            onClicked: root.activate();
            onReleased: root.Drag.drop();
            onWheel: wheel.accepted = false
        }

        IconToolButton {
            id: stopButton

            anchors {
                top: parent.top
                right: parent.right
            }
            visible: model.isActive
            padding: 0
            iconChar: MaterialIcons.icon_power_settings_new
            font.bold: true
            font.pixelSize: 16
            tooltip: qsTr("Stop")

            onClicked: mainWindow.runningServices.remove(model)

            Material.foreground: Material.Red
        }

        Rectangle {
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            color: "#404040"
            opacity: 0.9
            implicitHeight: layout.implicitHeight

            Material.theme: Material.Dark
            Material.foreground: "white"

            RowLayout {
                id: layout

                anchors.fill: parent
                spacing: 0

                IconToolButton {
                    id: starButton
                    padding: 0
                    iconChar: checked ? MaterialIcons.icon_star : MaterialIcons.icon_star_border
                    font.bold: true
                    font.pixelSize: 16
                    checkable: true
                    checked: model.favorite
                    tooltip: checked ? qsTr("Remove service from favorites") : qsTr("Add service to favorites")

                    onCheckedChanged: model.favorite = checked

                    Material.accent: Material.color(Material.Amber, Material.Shade600)
                }

                Item { Layout.fillWidth: true }

                IconToolButton {
                    id: settingsButton

                    padding: 0
                    iconChar: MaterialIcons.icon_settings
                    font.pixelSize: 16

                    tooltip: qsTr("App.settings")

                    onClicked: {
                        settingsDialog.service = model;
                        settingsDialog.open()
                    }
                }
            }

            Text {
                id: lblName

                anchors.centerIn: parent
                color: "white"
                text: model.name
                font.bold: true
            }
        }
    }

    function activate() {
        mainWindow.activateService(service);
    }
}
