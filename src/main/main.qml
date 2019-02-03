import QtQuick 2.9

import MellowPlayer 3.0

Item {
    id: root

    MainWindow {
        id: mainWindow_

        visible: true

        Component.onCompleted: _devTools.showDevTools()
    }

    property Component devToolsWindowComponent: DevToolsWindow {
        onClosing: destroy();
    }

    Connections {
        target: _devTools
        onShowDevTools: devToolsWindowComponent.createObject(root)
    }
}
