import QtQuick 2.15
import QtQuick.Controls 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0

MainAppWindow {
    id: root

    Connections {
        target: DevToolsWindow

        function onShow() {
            console.warn("Show dev tools window")
            var window = devToolsWindowComponent.createObject(root)
            window.show()
        }
    }

    property Component devToolsWindowComponent: ApplicationWindow {
        title: webView.title
        width: 800
        height: 600

        onClosing: destroy()

        WebEngineView {
            id: webView

            anchors.fill: parent
            url: "http://127.0.0.1:4242"
        }
    }
}
