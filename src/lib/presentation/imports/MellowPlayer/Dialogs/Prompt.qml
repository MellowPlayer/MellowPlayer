import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10

Dialog {
    id: root

    property JavaScriptDialogRequest request

    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    title: request.message

    onAccepted: request.dialogAccept(textField.text)
    onRejected: request.dialogReject()

    Material.accent: ActiveTheme.accent === ActiveTheme.background ? ActiveTheme.foreground : ActiveTheme.accent

    TextField {
        id: textField
        anchors.fill: parent
        text: request.defaultText
        selectByMouse: true
    }

    Shortcut {
        sequence: "Return"
        onActivated: accept()
    }

    Shortcut {
        sequence: "Enter"
        onActivated: accept()
    }
}
