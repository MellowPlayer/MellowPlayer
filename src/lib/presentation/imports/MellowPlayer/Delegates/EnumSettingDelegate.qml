import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

ItemDelegate {
    id: root

    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property Setting qtObject

    property EnumSetting enumSetting: qtObject
    property var values: enumSetting.values

    bottomPadding: 3; topPadding: 3
    hoverEnabled: true
    enabled: root.enabled
    onClicked: comboBox.popup.open()

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

        ComboBox {
            id: comboBox

            hoverEnabled: true
            model: values
            currentIndex: root.values.indexOf(root.qtObject.value)
            onCurrentTextChanged: qtObject.value = currentText

            Tooltip {
                text: SettingsTranslator.translateToolTip(root.toolTip)
            }
        }
    }
}
