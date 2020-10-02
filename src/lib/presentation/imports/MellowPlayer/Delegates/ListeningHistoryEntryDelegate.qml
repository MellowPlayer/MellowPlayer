import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick 2.15

import MellowPlayer 3.0

import "../Dialogs.js" as Dialogs
import "../DateCategoryTranslator.js" as DateCategoryTranslator

Frame {
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

    background: Rectangle {
        color: "transparent"
        visible: root.index != root.view.count - 1

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
            height: 1
            visible: root.expanded
        }
    }
    clip: true
    padding: 1
    hoverEnabled: true
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

    Pane {
        anchors.fill: parent
        padding: 0
        leftPadding: 12
        rightPadding: 12

        RowLayout {
            anchors.fill: parent
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
                    width: 250
                }

                Label {
                    text: qsTr("by") + " " + root.artist
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 250
                }

                Label {
                    text: qsTr("on") + " " + root.service
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 250
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Label {
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
    }

    Pane {
        id: controlPane

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        opacity: 0.9
        visible: false
        padding: 0

        RowLayout {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            ToolButton {
                id: btDelete
                hoverEnabled: true
                text: MaterialIcons.icon_delete
                font { family: MaterialIcons.family; pixelSize: 16 }
                onClicked: {
                    Dialogs.askConfirmation(
                        qsTr("Confirm remove"),
                        qsTr('Are you sure you want to remove that song from the history?'),
                        (confirmed) => {
                            if (confirmed)
                                ListeningHistoryViewModel.removeById(root.entryId)
                        }
                    )
                }

                Layout.fillHeight: true
            }

            ToolButton {
                id: btCopy
                hoverEnabled: true
                text: MaterialIcons.icon_content_copy
                font { family: MaterialIcons.family; pixelSize: 16 }
                onClicked: ClipBoardViewModel.setText(root.title)

                Layout.fillHeight: true
            }
        }
    }
}
