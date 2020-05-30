import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import MellowPlayer 3.0

StackLayout {
    id: root

    property WebView currentWebView: itemAt(currentIndex)

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
        webViewComponent.createObject(root, {"service": service} );
        service.isActive = true;
    }

    function remove(service) {
        var index = indexOf(service);
        if (index === currentIndex) {
            currentIndex = -1;
            _streamingServices.currentService = null;
            mainWindow.page = mainWindow.selectServicePage;
        }
        itemAt(index).destroy();
        service.isActive = false;
    }

    function exitFullScreen() {
        currentWebView.exitFullScreen();
    }

    function goBack() {
        currentWebView.goBack();
    }

    function goHome() {
        currentWebView.url = currentWebView.service.url;
        currentWebView.reload();
    }

    function goForward() {
        currentWebView.goForward();
    }

    function reload() {
        currentWebView.reload();
    }

    Shortcut {
        sequence: "Ctrl++"
        onActivated: currentWebView.zoomIn()
    }

    Shortcut {
        sequence: "Ctrl+-"
        onActivated: currentWebView.zoomOut()
    }

    Shortcut {
        sequence: "Ctrl+0"
        onActivated: currentWebView.resetZoom()
    }


    Shortcut {
        property var setting: _settings.get(SettingKey.SHORTCUTS_SELECT_NEXT_SERVICE)

        sequence: setting.value
        onActivated: _streamingServices.next()
    }

    Shortcut {
        property var setting: _settings.get(SettingKey.SHORTCUTS_SELECT_PREVIOUS_SERVICE)

        sequence: setting.value
        onActivated: _streamingServices.previous()
    }

    Connections {
        target: _streamingServices
        onCurrentServiceChanged: currentIndex = indexOf(_streamingServices.currentService)
    }

    Component {
        id: webViewComponent;

        WebView { }
    }
}
