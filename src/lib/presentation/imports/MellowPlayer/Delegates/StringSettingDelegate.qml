import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

ItemDelegate {
    bottomPadding: 3; topPadding: 3
    enabled: model.enabled
    hoverEnabled: true

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
            text: SettingsTranslator.translateName(model.name)
            font.pixelSize: 16
        }

        TextField {
            id: textField

            hoverEnabled: true
            placeholderText: model.name
            text: model.qtObject.value
            selectByMouse: true

            Layout.fillWidth: true

            onEditingFinished: model.qtObject.value = text

            Tooltip {
                text: SettingsTranslator.translateToolTip(model.toolTip)
            }
        }
    }
}
