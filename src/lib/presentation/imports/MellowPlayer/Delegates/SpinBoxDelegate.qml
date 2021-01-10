import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material.impl 2.15

import MellowPlayer 3.0

ItemDelegate {
    id: root

    property string label: ""
    property int value: 0
    property int from: 0
    property int to: 65535

    property var valueFromText: function(text, locale) { return Number.fromLocaleString(locale, text); }
    property var textFromValue: function(value, locale) { return Number(value).toLocaleString(locale, 'f', 0); }

    hoverEnabled: !ApplicationViewModel.hasTouchScreen

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 16
        spacing: 12

        Label {
            text: root.label
            enabled: root.enabled
        }

        Item {
            Layout.fillWidth: true
        }

        SpinBox {
            id: spinBox
            enabled: root.enabled
            editable: true
            value: root.value
            from: root.from
            to: root.to
            valueFromText: root.valueFromText
            textFromValue: root.textFromValue

            onValueChanged: root.value = value;
        }
    }
}
