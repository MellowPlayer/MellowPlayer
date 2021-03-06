import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Dialog {
    id: root

    readonly property int dialogAccepted: 0
    readonly property int dialogRejected: 1

    property int dialogResult: dialogRejected
    property string message: ""

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2
    modal: true
    width: 340

    onAccepted: dialogResult = dialogAccepted
    onRejected: dialogResult = dialogRejected

    Material.accent: ThemeViewModel.accent === ThemeViewModel.background ? ThemeViewModel.foreground : ThemeViewModel.accent

    Label {
        anchors.fill: parent
        text: root.message
        wrapMode: "WordWrap"
    }

    Shortcut {
        sequence: "Return"
        onActivated: root.accept()
        onActivatedAmbiguously: root.accept()
        enabled: root.visible
    }

    Shortcut {
        sequence: "Enter"
        onActivated: root.accept()
        onActivatedAmbiguously: root.accept()
        enabled: root.visible
    }
}
