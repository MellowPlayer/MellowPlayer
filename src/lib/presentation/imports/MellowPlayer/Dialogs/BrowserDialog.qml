import QtQuick 2.15
import QtQuick.Window 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs

Window {
    id: window

    function open(request, profile) {
        webView.profile = profile
        request.openIn(webView)
        showNormal()
    }

    flags: Qt.Dialog
    width: 1280
    height: 720

    // @disable-check M16
    onClosing: window.destroy()

    WebEngineView {
        id: webView

        anchors.fill: parent
        visible: window.visible

        onWindowCloseRequested: window.close();
        onNewViewRequested: (request) => {
            if (request.userInitiated) {
                console.log("opening web popup", request.requestedUrl)
                Dialogs.openWebPopup(request, webView.profile)
            }
        }
    }
}
