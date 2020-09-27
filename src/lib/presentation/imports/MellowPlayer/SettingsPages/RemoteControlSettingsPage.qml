import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Item {
    clip: true

    Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

    StackLayout {
        anchors.fill: parent
        currentIndex: RemoteControl.currentStateIndex

        Repeater {
            model: RemoteControl.states

            Loader {
                source: model.qmlComponent

                width: parent.width
                height: parent.height
            }
        }
    }

    Connections {
        target: RemoteControl

        function onError(title, message) {
            errorDialog.title = title
            errorDialog.message = message
            errorDialog.open()
        }
    }
}
