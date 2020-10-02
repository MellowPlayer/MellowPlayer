import QtQuick 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import MellowPlayer 3.0
import "../SettingsTranslator.js" as SettingsTranslator

ItemDelegate {
    id: root

    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property SettingViewModel qtObject

    bottomPadding: 3; topPadding: 3
    enabled: isEnabled
    hoverEnabled: true
    onClicked: colorDialog.open()

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: parent.leftPadding
        anchors.rightMargin: parent.rightPadding
        anchors.topMargin: parent.topPadding
        anchors.bottomMargin: parent.bottomPadding

        Label {
            text: SettingsTranslator.translateName(root.name)
            Layout.fillWidth: true
        }

        Button {
            hoverEnabled: true
            text: root.qtObject.value
            onTextChanged: root.qtObject.value = text
            onClicked: colorDialog.open()

            Material.background: root.qtObject.value
            Material.foreground: ThemeViewModel.isDark(root.qtObject.value) ? "white" : "#303030"

            Tooltip {
                text: SettingsTranslator.translateToolTip(root.toolTip)
            }

            ColorDialog {
                id: colorDialog

                title: qsTr("Please choose a color")
                color: root.qtObject.value
                onColorChanged: root.qtObject.value = color
            }
        }
    }
}
