import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

ItemDelegate {
    id: root

    bottomPadding: 3; topPadding: 3
    enabled: root.enabled
    hoverEnabled: true
    
    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property Setting qtObject
    

    onClicked: textField.forceActiveFocus()

    RowLayout {
        id: layout

        anchors {
            fill: parent
            leftMargin: parent.leftPadding
            rightMargin: parent.rightPadding
            topMargin: parent.topPadding
            bottomMargin: parent.bottomPadding
        }
        spacing: 16

        Label {
            text: SettingsTranslator.translateName(root.name)
        }

        TextField {
            id: textField

            hoverEnabled: true
            placeholderText: root.name
            text: root.qtObject.value
            selectByMouse: true

            Layout.fillWidth: true

            onEditingFinished: root.qtObject.value = text

            Tooltip {
                text: SettingsTranslator.translateToolTip(root.toolTip)
            }
        }
    }
}
