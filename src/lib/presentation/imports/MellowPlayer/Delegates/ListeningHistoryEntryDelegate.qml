import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Frame {
    id: root

    property bool expanded: false

    height: expanded ? 72 : 0; width: ListView.view.width

    background: Rectangle {
        color: "transparent"
        visible: index != listView.count - 1

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: ActiveTheme.isDark(ActiveTheme.background) ? Qt.lighter(ActiveTheme.background) : Qt.darker(ActiveTheme.background, 1.1)
            height: 1
            visible: expanded
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
                source: model.artUrl
                antialiasing: true
                mipmap: true
                smooth: true

                Layout.preferredHeight: 48
                Layout.preferredWidth: 48
            }

            Column {
                Label {
                    text: model.title
                    elide: "ElideMiddle"
                    font.bold: true
                    width: 250
                }

                Label {
                    text: qsTr("by") + " " + model.artist
                    font.italic: true
                    elide: "ElideMiddle"
                    width: 250
                }

                Label {
                    text: qsTr("on") + " " + model.service
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
                    if (model.dateCategory === "Today" || model.dateCategory === "Yesterday")
                        return DateCategoryTranslator.translate(model.dateCategory) + "\n" + model.time
                    else
                        return model.date + "\n" + model.time
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
                    messageBoxConfirmDelete.message = qsTr('Are you sure you want to remove that song from the history?')
                    messageBoxConfirmDelete.title = qsTr("Confirm remove")
                    messageBoxConfirmDelete.closed.connect(onActivated);
                    messageBoxConfirmDelete.open()
                }

                function onActivated() {
                    messageBoxConfirmDelete.closed.disconnect(onActivated);
                    if (messageBoxConfirmDelete.dialogResult === messageBoxConfirmDelete.dialogAccepted)
                        ListeningHistory.removeById(model.entryId)
                }

                Layout.fillHeight: true
            }

            ToolButton {
                id: btCopy
                hoverEnabled: true
                text: MaterialIcons.icon_content_copy
                font { family: MaterialIcons.family; pixelSize: 16 }
                onClicked: ClipBoard.setText(model.title)

                Layout.fillHeight: true
            }
        }
    }
}
