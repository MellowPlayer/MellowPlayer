import QtQuick 2.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

SwitchDelegate {
    id: root

    required property bool isEnabled
    required property string name
    required property string toolTip
    required property string type
    required property string qmlComponent
    required property Setting qtObject

    bottomPadding: 3; topPadding: 3
    anchors.fill: parent
    enabled: root.enabled
    checkable: true
    checked: root.qtObject.value
    hoverEnabled: true
    text: SettingsTranslator.translateName(root.name)

    onToggled: {
        console.warn("onToggled", root.name, checked, root.qtObject.value)
        root.qtObject.value = checked
    }

    Tooltip
    {
        text: SettingsTranslator.translateToolTip(root.toolTip)
    }
}
