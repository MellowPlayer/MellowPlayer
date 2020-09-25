import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0

Page {
    id: page

    signal quitRequested()

    Shortcut {
        sequence: "Escape"
        enabled: page.visible

        onActivated: page.quitRequested()
    }

    ServicesOverview {
        anchors.fill: parent
    }
}

