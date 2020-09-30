import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0
import "../SettingsTranslator.js" as SettingsTranslator

ItemDelegate {
    id: root

    bottomPadding: 3; topPadding: 3
    hoverEnabled: true
    enabled: root.enabled
    
    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property Setting qtObject

    property ScalingFactorSetting intSetting: qtObject

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

        SpinBox {
            value: root.qtObject.value
            from: root.intSetting.minValue
            to: root.intSetting.maxValue
            stepSize: root.qtObject.step

            textFromValue:  function(value, locale) {
                return Number(value).toLocaleString(locale, 'f', 0) + root.qtObject.suffix;
            }

            onValueChanged: root.qtObject.value = value

            Tooltip {
                text: SettingsTranslator.translateToolTip(root.toolTip)
            }
        }
    }
}
