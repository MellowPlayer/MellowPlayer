import QtQuick 2.9

import MellowPlayer 3.0

Item {
    id: root

    MainWindow {
        id: mainWindow_

        visible: true
    }

    property Component devToolsWindowComponent: DevToolsWindow {
        visible: true
        onClosing: destroy();
    }

    Connections {
        target: _devTools

        onShowDevTools: {
            console.warn("ShowDevTools")
            devToolsWindowComponent.createObject(root)
        }
    }
}
