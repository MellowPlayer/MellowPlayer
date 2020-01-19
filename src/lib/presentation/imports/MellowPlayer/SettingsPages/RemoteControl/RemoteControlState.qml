import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

Item {
    id: root

    property string title: ""
    property string message: ""
    property string icon: ""
    property bool buttonVisible: true
    property string buttonColor: Material.color(Material.Green, _theme.isDark(_theme.primary) ? Material.Shade600 : Material.Shade300)
    property string buttonText: ""
    property bool busyIndicatorVisible: false
    property bool autoStartCheckBoxVisible: false
    property bool footerVisible: true
    property string versionMessage:  qsTr("<a href=\"%3\">%1</a> <i>%2</i>").arg(_remoteControl.appInfo.name).arg(_remoteControl.appInfo.version).arg(_remoteControl.appInfo.homePage)

    signal buttonClicked()

    Page {
        anchors.fill: parent

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 32

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Label {
                text: root.icon
                font.pixelSize: 96
                font.family: MaterialIcons.family

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Label {
                text: root.title
                font.bold: true
                font.pixelSize: 32

                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Link {
                text: root.message
                horizontalAlignment: "AlignHCenter"

                Layout.fillWidth: true
            }

            Button {
                visible: root.buttonVisible
                text: root.buttonText
                highlighted: true
                hoverEnabled: true
                onClicked: root.buttonClicked()

                Material.accent: root.buttonColor
                Layout.alignment: Qt.AlignCenter
            }

            BusyIndicator {
                visible: root.busyIndicatorVisible
                implicitWidth: 48
                implicitHeight: 48
                running: true

                Layout.alignment: Qt.AlignHCenter
            }

            Item {
                Layout.fillHeight: true
            }

            CheckBox {
                checked: _remoteControl.autoStartEnabled
                visible: root.autoStartCheckBoxVisible
                text: qsTr("Run at startup")

                onToggled: _remoteControl.autoStartEnabled = checked

                Layout.alignment: Qt.AlignHCenter
            }
        }

        footer: Pane {
            visible: footerVisible
            padding: 17
            implicitHeight: layout.implicitHeight + padding * 2
            implicitWidth: layout.implicitWidth

            Material.elevation: 3

            RowLayout {
                id: layout

                anchors.fill: parent
                spacing: 12

                Image {
                    source: _remoteControl.appInfo.logo

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredHeight: 38
                    Layout.preferredWidth: 38

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        hoverEnabled: true

                        onClicked: Qt.openUrlExternally(_remoteControl.appInfo.homePage)
                    }
                }

                Link {
                    text: root.versionMessage
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: qsTr("Disable Remote Control")
                    flat: true
                    highlighted: true

                    onClicked: _remoteControl.deactivate()
                }
            }
        }
    }
}
