import QtQuick 2.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

ToolButton {
    id: root

    property string shortcut: ""
    property string tooltip: ""
    property string iconChar: ""
    property int iconSize: 22

    signal triggered()

    text: iconChar
    font { family: MaterialIcons.family; pixelSize: iconSize }
    hoverEnabled: !ApplicationViewModel.hasTouchScreen
    padding: 0
    spacing: 0

    onClicked: if (!checkable) triggered()

    Tooltip {
        y: parent.implicitHeight
        text: root.tooltip
        shortcut: root.shortcut
    }

    Shortcut {
        sequence: root.shortcut
        onActivated: root.triggered()
    }
}
