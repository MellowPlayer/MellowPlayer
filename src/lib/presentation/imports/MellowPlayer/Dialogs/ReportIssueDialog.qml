import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs

Dialog {
    id: root

    modal: true
    padding: 16
    width: 340
    height: 340
    title: qsTr("Report issue")

    onVisibleChanged: stackLayout.currentIndex = 0
    Component.onCompleted: Dialogs.keepCenteredOnMainWindow(root)

    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: 0

        ColumnLayout {
            spacing: 0

            Layout.fillHeight: true
            Layout.fillWidth: true

            RadioButton {
                id: reportOnGitlabRadioButton

                checked: true
                text: qsTr("Report the issue on gitlab")
            }

            RadioButton {
                text: qsTr("Report the issue via e-mail")
            }

            Item { Layout.fillHeight: true }

            Link {
                name: qsTr("Please, read the contributing guidelines before submitting the bug report!")
                url: "https://gitlab.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.md#reporting-bugs-or-wishes"
                horizontalAlignment: Qt.AlignHCenter
                wrapMode: "WordWrap"
                font.pixelSize: 16
                font.bold: true

                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Report issue")
                highlighted: true

                onClicked: {
                    if (reportOnGitlabRadioButton.checked) {
                        Qt.openUrlExternally("https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/new?issue")
                    } else {
                        Qt.openUrlExternally("mailto: incoming+ColinDuquesnoy/MellowPlayer@incoming.gitlab.com")
                    }
                    stackLayout.currentIndex = 1;
                }

                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 12
            }
        }

        Pane {
            padding: 16

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.fillHeight: true
                }

                Label {
                    text: qsTr("Thank you for taking the time to report the issue!")
                    font.bold: true
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: "WordWrap"

                    Layout.fillWidth: true
                }

                Label {
                    text: MaterialIcons.icon_thumb_up
                    font { family: MaterialIcons.family; pixelSize: 48 }

                    Layout.alignment: Qt.AlignHCenter
                    Layout.topMargin: 6
                }

                Item {
                    Layout.fillHeight: true
                }

                Button {
                    text: qsTr("Close")
                    highlighted: true

                    onClicked: root.close()

                    Layout.alignment: Qt.AlignHCenter
                }

            }
        }
    }
}
