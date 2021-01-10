import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick 2.15

import MellowPlayer 3.0

import "../Dialogs.js" as Dialogs
import "../DateCategoryTranslator.js" as DateCategoryTranslator

SwipeDelegate {
    id: root

    required property ListView view
    required property int index
    required property string artUrl
    required property string title
    required property string artist
    required property string service
    required property string dateCategory
    required property string date
    required property string time
    required property string entryId
    required property Drawer drawer

    property bool expanded: false

    height: expanded ? 72 : 0; width: view.width
    hoverEnabled: !ApplicationViewModel.hasTouchScreen
    clip: true
    padding: 1
    onHoveredChanged: {
        if (hovered) {
            delayTimer.start();
        }
        else {
            delayTimer.stop();
            controlPane.visible = false
        }
    }

    Behavior on height {
        NumberAnimation { duration:  100 }
    }

    swipe.enabled: ApplicationViewModel.hasTouchScreen
    swipe.left: Label {
        id: deleteLabel
        text: MaterialIcons.icon_delete
        font { family: MaterialIcons.family; pixelSize: 16 }
        color: "white"
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignHCenter
        padding: 12
        height: parent.height
        width: 64
        anchors.left: parent.left

        SwipeDelegate.onClicked: { d.remove(); }

        background: Rectangle {
            color: Material.color(Material.Red)

            Rectangle {
                anchors.fill: parent
                color: Material.foreground
                opacity: 0.24
                visible: deleteLabel.SwipeDelegate.pressed
            }
        }
    }

    swipe.right: Label {
        id: copyLabel
        text: MaterialIcons.icon_content_copy
        font { family: MaterialIcons.family; pixelSize: 16 }
        color: "white"
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignHCenter
        padding: 12
        height: parent.height
        width: 64
        anchors.right: parent.right

        SwipeDelegate.onClicked: { d.copy(); }

        background: Rectangle {
            color: Material.accent

            Rectangle {
                anchors.fill: parent
                color: Material.foreground
                opacity: 0.24
                visible: copyLabel.SwipeDelegate.pressed
            }
        }
    }

    ListView.onRemove: SequentialAnimation {
        PropertyAction { target: root; property: "ListView.delayRemove"; value: true }
        NumberAnimation { target: root; property: "x"; to: 950; duration: 200 ; easing.type: Easing.InOutQuad }
        PropertyAction { target: root; property: "ListView.delayRemove"; value: false }
    }

    Timer {
        id: delayTimer
        interval: 400
        onTriggered: controlPane.visible = true
    }

    contentItem: Item {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            spacing: 8

            Image {
                source: root.artUrl
                antialiasing: true
                mipmap: true
                smooth: true

                Layout.preferredHeight: 48
                Layout.preferredWidth: 48
            }

            Column {
                Label {
                    text: root.title
                    elide: "ElideMiddle"
                    font.bold: true
                    width: 140
                }

                Label {
                    text: qsTr("by") + " " + root.artist
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 140
                }

                Label {
                    text: qsTr("on") + " " + root.service
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 140
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Label {
                visible: !controlPane.visible
                text: {
                    if (root.dateCategory === "Today" || root.dateCategory === "Yesterday")
                        return DateCategoryTranslator.translate(root.dateCategory) + "\n" + root.time
                    else
                        return root.date + "\n" + root.time
                }
                verticalAlignment: "AlignVCenter"
                horizontalAlignment:"AlignRight"
            }
        }

        Item {
            id: controlPane

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 12
            visible: false

            RowLayout {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right

                ToolButton {
                    id: btDelete
                    hoverEnabled: !ApplicationViewModel.hasTouchScreen
                    text: MaterialIcons.icon_delete
                    font { family: MaterialIcons.family; pixelSize: 16 }
                    onClicked: { d.remove(); }

                    Layout.fillHeight: true
                }

                ToolButton {
                    id: btCopy
                    hoverEnabled: !ApplicationViewModel.hasTouchScreen
                    text: MaterialIcons.icon_content_copy
                    font { family: MaterialIcons.family; pixelSize: 16 }
                    onClicked: { d.copy() }

                    Layout.fillHeight: true
                }
            }
        }
    }

    QtObject {
        id: d

        function remove() {
            Dialogs.askConfirmation(
                qsTr("Confirm remove"),
                qsTr('Are you sure you want to remove that song from the history?'),
                (confirmed) => {
                    if (confirmed)
                        ListeningHistoryViewModel.removeById(root.entryId)
                }
            )
        }

        function copy() {
            ClipBoardViewModel.setText(root.title)
        }
    }
}
