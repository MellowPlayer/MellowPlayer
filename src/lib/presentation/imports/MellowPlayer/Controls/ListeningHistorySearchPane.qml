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

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: searchField

            focus: true
            placeholderText: qsTr("Search by title or by artist")
            onEnabledChanged: {
                if (enabled) {
                    focus = true;
                    forceActiveFocus();
                }
            }
            selectByMouse: true
            onTextChanged: ListeningHistory.setSearchFilter(text)

            Tooltip {
                text: qsTr("Filter song by title or by artist")
            }

            Layout.fillWidth: true
        }

        Flow {
            id: filters
            spacing: 3

            width: parent.width

            Repeater {
                z: 1
                model: StreamingServices.filteredServices

                Button {
                    id: filter

                    required property string name

                    flat: true
                    checkable: true; checked: true
                    hoverEnabled: true
                    text: filter.name

                    onCheckedChanged: {
                        ListeningHistory.disableService(filter.name, !checked)
                    }

                    Tooltip {
                        text: filter.checked ? qsTr("Click to remove songs from")  + filter.name : qsTr("Click to add songs from ") + filter.name
                    }
                }
            }
        }
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

            PropertyChanges {
                target: filters
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

            PropertyChanges {
                target: filters
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
