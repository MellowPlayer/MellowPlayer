import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

WizardPage {
    property alias svName: fieldSvName.text
    property alias svUrl: fieldSvUrl.text
    property alias authorName: fieldAuthor.text
    property alias authorUrl: fieldAuthorWebsite.text
    property alias allPlatforms: cbAllPlatforms.checked
    property alias linuxPlatform: cbLinuxPlatform.checked
    property bool appImagePlatform: false
    property bool osxPlatform: false
    property alias windowsPlatform: cbWindowsPlatform.checked

    title: qsTr("Details")
    description: qsTr("Please fill in the details about your plugin")
    goBackVisible: true
    goNextVisible: true
    finishVisible: false
    goNextEnabled: fieldSvName.text != "" && fieldSvUrl.text != "" && fieldAuthor.text != "" && fieldAuthorWebsite.text != "" && hasAtLeastOnePlaformSelected();

    function hasAtLeastOnePlaformSelected() {
        if (allPlatforms)
            return true;

        if (linuxPlatform)
            return true;

        if (windowsPlatform)
            return true;

        return false;
    }

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            Layout.fillWidth: true

            columns: 2
            rows: 4

            Label {
                text: qsTr("Service name:")
            }

            TextField {
                id: fieldSvName

                focus: true
                selectByMouse: true

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Service URL:")
            }

            TextField {
                id: fieldSvUrl

                selectByMouse: true

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Author:")
            }

            TextField {
                id: fieldAuthor

                selectByMouse: true

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Author website:")
            }

            TextField {
                id: fieldAuthorWebsite

                selectByMouse: true

                Layout.fillWidth: true
            }

            ColumnLayout {
                Item {
                    height: 12
                }

                Label {
                    text: qsTr("Supported platforms:")
                }

                Item {
                    Layout.fillHeight: true
                }
            }

            Flow {
                CheckBox {
                    id: cbAllPlatforms

                    text: qsTr("All")
                }

                CheckBox {
                    id: cbLinuxPlatform

                    text: "GNU/Linux"
                    enabled: !cbAllPlatforms.checked
                }

                CheckBox {
                    id: cbWindowsPlatform

                    text: "Windows"
                    enabled: !cbAllPlatforms.checked
                }
            }

        }

        Item {
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: {
        fieldSvName.forceActiveFocus()
        cbAllPlatforms.checked = true;
    }
}
