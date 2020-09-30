import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Pane {
    id: root

    property string customUrl

    signal reloadRequested()

    function open() {
        state = "visible";
    }

    Material.background: ActiveTheme.primary
    Material.foreground: ActiveTheme.primaryForeground
    Material.elevation: 4

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Custom url required")
            font.bold: true
            font.pixelSize: 14

            Layout.alignment: Qt.AlignCenter
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: textField

                selectByMouse: true
                text: root.customUrl
                onEditingFinished: save()

                function save() {
                    root.customUrl = text;
                    root.state = "hidden";
                }

                Layout.fillWidth: true
            }

            ToolButton {
                flat: true
                font.family: MaterialIcons.family
                font.pixelSize: 24
                text: MaterialIcons.icon_done

                onClicked: textField.save()
            }
        }
    }

    state: "hidden"
    states: [
        State {
            name: "hidden"

            PropertyChanges {
                target: root
                y: -root.implicitHeight - 16
            }
        },
        State {
            name: "visible"

            PropertyChanges {
                target: root
                y: -2
            }
        }
    ]
    transitions: Transition {
        from: "visible"
        to: "hidden"
        reversible: true

        PropertyAnimation {
            properties: "y"
        }

        onRunningChanged: {
            if (root.state == "hidden" && !running)
                root.reloadRequested()
        }

    }
}
