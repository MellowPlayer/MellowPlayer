import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Pane {
    id: root

    property string text: ClipBoardViewModel.copiedText

    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.rightMargin: 8
    anchors.leftMargin: 8
    anchors.bottomMargin: 4
    visible: state === "visible"

    onTextChanged: {
        console.warn("txt changed", text)
        if (text !== "") {
            state = "visible";
            disappearTimer.restart();
        }
        else
            state = "hidden"
    }

    Material.background: ThemeViewModel.primary
    Material.foreground: ThemeViewModel.primaryForeground
    Material.elevation: 4

    Component.onCompleted: { background.opacity = 0.98 }

    Column {
        anchors.fill: parent
        spacing: 4

        Label {
            height: implicitHeight; width: parent.width
            elide: "ElideMiddle"
            font.pixelSize: 16
            font.bold: true
            horizontalAlignment: "AlignHCenter"
            text: root.text
        }

        Label {
            height: implicitHeight; width: parent.width
            horizontalAlignment: "AlignHCenter"
            text: qsTr('copied to clipboard')
        }
    }

    Timer {
        id: disappearTimer
        interval: 3000
        onTriggered: root.state = "hidden"
    }

    state: "hidden"
    states: [
        State {
            name: "hidden"

            PropertyChanges {
                target: root
                opacity: 0
            }
        },
        State {
            name: "visible"

            PropertyChanges {
                target: root
                opacity: 1
            }
        }
    ]
    transitions: Transition {
        from: "hidden"
        to: "visible"
        reversible: true

        PropertyAnimation {
            properties: "opacity"
        }
    }
}
