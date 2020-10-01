import QtQuick 2.15
import QtQuick.Controls 2.15

ToolTip {
    id: root

    property string shortcut: ""

    visible: parent !== undefined ? root.parent.hovered : false
    delay: 1000
    timeout: 5000
    y: parent.implicitHeight
    x: 0

    contentItem: Text {
        text: root.text + (root.shortcut != "" ? " (" + root.shortcut + ")" : "")
        font: root.font
        color: "white"
    }

    background: Rectangle {
        color: "#606060"
        opacity: 0.9
        radius: 2
    }
}
