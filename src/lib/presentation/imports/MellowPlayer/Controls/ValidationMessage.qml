import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Pane {
    property alias text: label.text

    visible: false
    z: 1

    Material.background: ThemeViewModel.primary
    Material.foreground: ThemeViewModel.primaryForeground
    Material.elevation: 4

    Label {
        id: label

        anchors.fill: parent
    }
}

