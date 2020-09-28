import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQml 2.15

import MellowPlayer 3.0

import "../Dialogs.js" as Dialogs

Item {
    id: root

    clip: true

    property RemoteControlError error: RemoteControl.error

    onErrorChanged: {
        if (error) {
            Dialogs.showError(root.error.title, root.error.message)
        }
    }

    Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

    StackLayout {
        anchors.fill: parent
        currentIndex: RemoteControl.currentStateIndex

        Repeater {
            model: RemoteControl.states

            Loader {
                id: loader

                required property string qmlComponent

                source: loader.qmlComponent

                width: parent.width
                height: parent.height
            }
        }
    }
}
