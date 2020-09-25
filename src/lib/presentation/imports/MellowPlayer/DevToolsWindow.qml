import QtQuick 2.15
import QtQuick.Controls 2.15
import QtWebEngine 1.10

ApplicationWindow {
    id: devToolsWindow

    property string url: "http://127.0.0.1:4242"

    title: webView.title
    visible: mainWindow_.visible
    width: 800
    height: 600

    WebEngineView {
        id: webView

        anchors.fill: parent
        url: devToolsWindow.url
    }

    Component.onCompleted: visible = true
}
