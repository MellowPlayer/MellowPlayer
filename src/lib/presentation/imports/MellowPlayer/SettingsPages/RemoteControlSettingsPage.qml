import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

Item {
    clip: true

    Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

    StackLayout {
        anchors.fill: parent
        currentIndex: _remoteControl.currentStateIndex

        Repeater {
            model: _remoteControl.states

            Loader {
                source: model.qmlComponent

                width: parent.width
                height: parent.height
            }
        }
    }

    Connections {
        target: _remoteControl
        onError: {
            errorDialog.title = title
            errorDialog.message = message
            errorDialog.open()
        }
    }
}
