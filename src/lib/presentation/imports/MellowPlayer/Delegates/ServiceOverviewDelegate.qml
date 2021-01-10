import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10
import QtGraphicalEffects 1.0

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs

ItemDelegate {
    id: root

    required property StreamingServiceViewModel service

    property int index: service.sortIndex
    property bool last: false
    property color backgroundColor: Material.background

    function activate() {
        root.activated()
        StreamingServicesViewModel.currentService = root.service
    }
    signal activated()

    hoverEnabled: !ApplicationViewModel.hasTouchScreen
    padding: 0
    highlighted: root.service === StreamingServicesViewModel.currentService

    onIndexChanged: service.sortIndex = root.index
    onClicked: activate()

    Component.onCompleted: service.sortIndex = root.index
    Drag.active: dragArea.drag.active
    Material.elevation: 4
    Layout.fillWidth: true
    Layout.fillHeight: true

    RowLayout {
        anchors.fill: parent
        anchors.margins: 0

        Item {
            Layout.preferredWidth: 24
            Layout.preferredHeight: 24
            Layout.alignment: Qt.AlignVCenter
            Layout.leftMargin: 6

            Label {
                anchors.centerIn: parent
                font.family: MaterialIcons.family
                font.pixelSize: 20
                font.bold: false
                text: MaterialIcons.icon_drag_handle
                opacity: root.Drag.active ? 0.88 : 0.48
            }

            MouseArea {
                id: dragArea

                anchors.fill: parent
                drag.target: root
                hoverEnabled: !ApplicationViewModel.hasTouchScreen
                propagateComposedEvents: true

                onReleased: root.Drag.drop();
            }
        }

        IconToolButton {
            id: starButton
            padding: 0
            iconChar: checked ? MaterialIcons.icon_star : MaterialIcons.icon_star_border
            font.bold: true
            font.pixelSize: 16
            checkable: true
            checked: root.service.favorite
            tooltip: checked ? qsTr("Remove root.service from favorites") : qsTr("Add root.service to favorites")
            focusPolicy: Qt.NoFocus

            onCheckedChanged: root.service.favorite = checked

            Material.accent: Material.color(Material.Amber, Material.Shade600)
        }

        Image {
            antialiasing: true
            height: 48; width: 48
            mipmap: true
            source: root.service.logo
            smooth: true

            Layout.preferredWidth: width
            Layout.preferredHeight: height
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Label {
            id: lblName

            text: root.service.name
            font.bold: true
            elide: "ElideRight"

            Layout.fillWidth: true
            Layout.leftMargin: 16
        }

        IconToolButton {
            id: settingsButton

            padding: 0
            iconChar: MaterialIcons.icon_settings
            font.pixelSize: 16
            focusPolicy: Qt.NoFocus

            tooltip: qsTr("Settings")

            onClicked: Dialogs.openServiceSettings(root.service)
        }

        IconToolButton {
            id: stopButton

            visible: root.service.isActive
            padding: 0
            iconChar: MaterialIcons.icon_power_settings_new
            font.bold: true
            font.pixelSize: 16
            tooltip: qsTr("Stop")
            focusPolicy: Qt.NoFocus

            onClicked: MainWindowViewModel.runningServices.remove(root.service)

            Material.foreground: Material.Red
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 6
        visible: root.service.isActive
        color: root.highlighted ? Material.accent : ThemeViewModel.foreground
        opacity: root.highlighted ? 0.64 : 0.24
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
        visible: !root.Drag.active && !root.last
    }
}