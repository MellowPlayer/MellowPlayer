import QtQuick 2.15
import QtQuick.Controls 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0

Item {
    id: root

    MainAppWindow {
        id: mainAppWindow

        visible: true
    }

    property Component devToolsWindowComponent: ApplicationWindow {
        id: devToolsWindow

        property string url: "http://127.0.0.1:4242"

        title: webView.title
        width: 800
        height: 600
        visible: mainAppWindow.visible

        onClosing: destroy();

        WebEngineView {
            id: webView

            anchors.fill: parent
            url: devToolsWindow.url
        }
    }

    Connections {
        target: DevToolsWindow

        function onShow() {
            console.warn("ShowDevTools")
            devToolsWindowComponent.createObject(root)
        }
    }
}
