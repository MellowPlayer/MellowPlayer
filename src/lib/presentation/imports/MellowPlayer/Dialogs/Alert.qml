import QtQuick 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0

// TODO QMLLINT

MessageBoxDialog {
    id: dialog

    property JavaScriptDialogRequest request

    title: request.title
    message: request.message;
    // standardButtons: MessageBoxDialog.Ok

    onAccepted: request.dialogAccept()
    onRejected: request.dialogReject()
}
