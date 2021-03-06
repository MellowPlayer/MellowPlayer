import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Pane {
    id: notif

    visible: false
    onVisibleChanged: if (visible) disappearTimer.running = true

    Material.elevation: 4
    Material.background: "#303030"
    Material.foreground: "#ffffff"
    Material.theme: Material.Dark

    Label {
        text: qsTr("<p>You are now in <b>fullscreen</b> mode.</p>Press <b>ESC</b> to quit!")
        font.pixelSize: 14
        horizontalAlignment: "AlignHCenter"
    }

    Timer {
        id: disappearTimer
        interval: 3000
        onTriggered: notif.visible = false;
    }

    Behavior on opacity { NumberAnimation { duration: 100 } }

    states: [
        State {
            when: notif.visible

            PropertyChanges {
                target: notif
                opacity: 0.8
            }
        },
        State {
            when: !notif.visible

            PropertyChanges {
                target: notif
                opacity: 0.0
            }
        }
    ]
}
