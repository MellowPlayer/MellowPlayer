import QtQuick 2.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

Drawer {
    id: root

    edge: Qt.RightEdge
    interactive: false

    Shortcut {
        enabled: root.visible
        sequence: "Escape"

        onActivatedAmbiguously: root.close()
    }

    SettingsPage {
        anchors.fill: parent

        onCloseRequested: root.close()
    }
}
