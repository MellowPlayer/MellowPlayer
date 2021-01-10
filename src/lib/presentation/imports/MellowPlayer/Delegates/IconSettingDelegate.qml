import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import MellowPlayer 3.0
import "../SettingsTranslator.js" as SettingsTranslator

ItemDelegate {
    id: root

    bottomPadding: 3; topPadding: 3
    enabled: root.enabled
    hoverEnabled: !ApplicationViewModel.hasTouchScreen
    
    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property SettingViewModel qtObject

    onClicked: fileDialog.open()

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: parent.leftPadding
        anchors.rightMargin: parent.rightPadding
        anchors.topMargin: parent.topPadding
        anchors.bottomMargin: parent.bottomPadding

        Label {
            text: SettingsTranslator.translateName(root.name)
        }

        Item { width: 16 }

        TextField {
            id: pathField

            placeholderText: "Custom icon path"
            text:  root.qtObject.value
            onTextChanged:  root.qtObject.value = text
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
