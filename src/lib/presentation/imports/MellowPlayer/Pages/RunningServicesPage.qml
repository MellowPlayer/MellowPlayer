import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

StackLayout {
    id: root

    property WebView currentWebView

    currentIndex: indexOf(StreamingServices.currentService)

    function indexOf(service) {
        if (service !== null) {
            for(var i = 0; i < count; i++) {
                if (itemAt(i).service.name === service.name)
                    return i;
            }
        }
        return -1;
    }

    function add(service) {
        webViewComponent.createObject(root, {"service": service, "index": root.count });
        service.isActive = true;
    }

    function remove(service) {
        var index = indexOf(service);
        if (index === currentIndex) {
            currentIndex = -1;
            StreamingServices.currentService = null;
            mainWindow.page = mainWindow.selectServicePage;
        }
        itemAt(index).destroy();
        service.isActive = false;
    }

    function exitFullScreen() {
        root.currentWebView.exitFullScreen();
    }

    function goBack() {
        root.currentWebView.goBack();
    }

    function goHome() {
        root.currentWebView.url = root.currentWebView.service.url;
        root.currentWebView.reload();
    }

    function goForward() {
        root.currentWebView.goForward();
    }

    function reload() {
        root.currentWebView.reload();
    }

    Shortcut {
        sequence: "Ctrl++"
        onActivated: root.currentWebView.zoomIn()
    }

    Shortcut {
        sequence: "Ctrl+-"
        onActivated: root.currentWebView.zoomOut()
    }

    Shortcut {
        sequence: "Ctrl+0"
        onActivated: root.currentWebView.resetZoom()
    }


    Shortcut {
        property Setting setting: App.settings.get(SettingKey.SHORTCUTS_SELECT_NEXT_SERVICE)

        sequence: setting.value
        onActivated: StreamingServices.next()
    }

    Shortcut {
        property Setting setting: App.settings.get(SettingKey.SHORTCUTS_SELECT_PREVIOUS_SERVICE)

        sequence: setting.value
        onActivated: StreamingServices.previous()
    }

    Component {
        id: webViewComponent

        WebView {
            id: webView

            required property int index
            property bool isCurrent: index === root.currentIndex

            onIsCurrentChanged: root.currentWebView = webView
        }
    }
}
