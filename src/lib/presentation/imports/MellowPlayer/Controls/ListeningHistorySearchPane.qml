import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Pane {
    id: root

    property bool isOpen: false

    clip: true

    onIsOpenChanged: searchField.text = ""

    Material.elevation: 2

    TextField {
        id: searchField
        anchors.fill: parent

        focus: true
        placeholderText: qsTr("Search by title or by artist")
        onEnabledChanged: {
            if (enabled) {
                focus = true;
                forceActiveFocus();
            }
        }
        selectByMouse: true
        onTextChanged: ListeningHistoryViewModel.setSearchFilter(text)

        Tooltip {
            text: qsTr("Filter song by title or by artist")
        }

        Layout.fillWidth: true
    }

    state: "closed"
    states: [
        State {
            name: "closed"
            when: !root.isOpen

            PropertyChanges {
                target: root
                height: 0
            }

            PropertyChanges {
                target: searchField
                enabled: false
            }
        },
        State {
            name: "open"
            when: root.isOpen

            PropertyChanges {
                target: root
                height: root.implicitHeight
            }

            PropertyChanges {
                target: searchField
                enabled: true

            }
        }
    ]

    transitions: Transition {
        from: "open"
        to: "closed"
        reversible: true

        PropertyAnimation { properties: "height"; easing.type: "InOutCubic" }
    }
}
