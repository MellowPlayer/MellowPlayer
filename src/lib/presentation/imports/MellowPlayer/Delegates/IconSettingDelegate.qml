import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import MellowPlayer 3.0

ItemDelegate {
    bottomPadding: 3; topPadding: 3
    enabled: model.enabled
    hoverEnabled: true

    onClicked: fileDialog.open()

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: parent.leftPadding
        anchors.rightMargin: parent.rightPadding
        anchors.topMargin: parent.topPadding
        anchors.bottomMargin: parent.bottomPadding

        Label {
            text: SettingsTranslator.translateName(model.name)
            font.pixelSize: 16
        }

        Item { width: 16 }

        TextField {
            id: pathField

            placeholderText: "Custom icon path"
            text:  model.qtObject.value
            onTextChanged:  model.qtObject.value = text
            selectByMouse: true

            Layout.fillWidth: true
        }

        ToolButton {
            text: "..."
            onClicked: fileDialog.open()
        }

        Image {
            source: pathField.text !== "" ? "file://" + pathField.text : ""
            sourceSize.height: 32
            sourceSize.width: 32
            width: 32
            height: 32
        }

        FileDialog {
            id: fileDialog

            title: "Please choose a custom tray icon"
            folder: shortcuts.home
            visible: false
            nameFilters:  [ "Image files (*.jpg *.png)", "All files (*)" ]

            onAccepted: {
                pathField.text = fileDialog.fileUrls[0].replace("file://", "")
            }
            onRejected: {
                console.log("Canceled")
            }
        }
    }
}
