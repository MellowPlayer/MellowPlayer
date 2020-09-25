import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

ItemDelegate {
    bottomPadding: 3; topPadding: 3
    hoverEnabled: true
    enabled: model.enabled

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: parent.leftPadding
        anchors.rightMargin: parent.rightPadding
        anchors.topMargin: parent.topPadding
        anchors.bottomMargin: parent.bottomPadding

        Label {
            text: SettingsTranslator.translateName(model.name)
            font.pixelSize: 16

            Layout.fillWidth: true
        }

        SpinBox {
            value: model.qtObject.value
            from: model.qtObject.minValue
            to: model.qtObject.maxValue
            stepSize: model.qtObject.step

            textFromValue:  function(value, locale) {
                return Number(value).toLocaleString(locale, 'f', 0) + model.qtObject.suffix;
            }

            onValueChanged: model.qtObject.value = value

            Tooltip {
                text: SettingsTranslator.translateToolTip(model.toolTip)
            }
        }
    }
}
