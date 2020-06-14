import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebEngine 1.5

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
    onClosing: destroy()

    WebEngineView {
        id: webView

        anchors.fill: parent
        visible: window.visible

        onWindowCloseRequested: window.close();
        onNewViewRequested: mainWindow.openWebPopup(request, profile)
    }
}
