import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQml 2.15

import MellowPlayer 3.0

Dialog {
    id: wizard

    property WizardPage currentPage: stackView.currentItem
    property string svName
    property string svUrl
    property string authorName
    property string authorUrl
    property string directory
    property bool allPlatforms
    property bool linuxPlatform
    property bool appImagePlatform
    property bool osxPlatform
    property bool windowsPlatform

    title: wizard.currentPage.title

    function restart() {
        while (stackView.depth > 1)
            stackView.pop()
    }

    function next() {
        stackView.push(wizard.currentPage.next)
    }

    function previous() {
        stackView.pop();
    }

    Component {
        id: startPage

        StartPage {
            next: detailsPage
            previous: null
        }
    }

    Component {
        id: detailsPage

        DetailsPage {
            next: creatingPage
            previous: startPage

            onSvNameChanged: wizard.svName = svName
            onSvUrlChanged: wizard.svUrl = svUrl
            onAuthorNameChanged: wizard.authorName = authorName
            onAuthorUrlChanged: wizard.authorUrl = authorUrl
            onAllPlatformsChanged: wizard.allPlatforms = allPlatforms
            onLinuxPlatformChanged: wizard.linuxPlatform = linuxPlatform
            onAppImagePlatformChanged: wizard.appImagePlatform = appImagePlatform
            onOsxPlatformChanged: wizard.osxPlatform = osxPlatform
            onWindowsPlatformChanged: wizard.windowsPlatform = windowsPlatform
        }
    }

    Component {
        id: creatingPage

        CreatingPage {
            next: finishPage
            previous: detailsPage
            svName: wizard.svName
            svUrl: wizard.svUrl
            authorName: wizard.authorName
            authorUrl: wizard.authorUrl
            allPlatforms: wizard.allPlatforms
            linuxPlatform: wizard.linuxPlatform
            appImagePlatform: wizard.appImagePlatform
            osxPlatform: wizard.osxPlatform
            windowsPlatform: wizard.windowsPlatform

            onGoNextRequested: wizard.next()
            onDirectoryChanged: wizard.directory = directory
        }
    }


    Component {
        id: finishPage

        FinishPage {
            next: null
            previous: creatingPage
            directory: wizard.directory
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: wizard.currentPage.description
            font.italic: true

            Layout.leftMargin: 24
        }

        Item {
            Layout.preferredHeight: 4
        }

        Rectangle {
            color: ActiveTheme.foreground
            opacity: 0.5

            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        Item {
            Layout.preferredHeight: 4
        }

        StackView {
            id: stackView

            initialItem: startPage
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    footer: Pane {
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 8
            anchors.topMargin: 8

            Button {
                id: openPluginDirectory

                highlighted: true
                text: qsTr("Open plugin directory")
                visible: wizard.currentPage.openPluginDirectoryVisible
                flat: true

                onClicked: Qt.openUrlExternally("file://" + wizard.directory)
            }

            Button {
                highlighted: true
                flat: true
                text: qsTr("Read API documentation")
                visible: !openPluginDirectory.visible

                onClicked: Qt.openUrlExternally("http://mellowplayer.readthedocs.org/en/latest/developers/plugins.html#functions-to-implement")
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                id: previousButton

                highlighted: true
                text: qsTr("Previous")
                visible: wizard.currentPage.goBackVisible
                flat: true

                onClicked: wizard.previous()
            }
            Button {
                id: nextButton

                highlighted: true
                flat: true
                text: qsTr("Next")
                enabled: wizard.currentPage.goNextEnabled
                visible: wizard.currentPage.goNextVisible

                onClicked: wizard.next()
            }

            Button {
                id: cancelButton

                highlighted: true
                flat: true
                text: qsTr("Cancel")
                visible: !wizard.currentPage.finishVisible

                onClicked: wizard.close()
            }

            Button {
                id: finishButton

                highlighted: true
                flat: true
                text: qsTr("Finish")
                visible: wizard.currentPage.finishVisible

                onClicked: wizard.close()
            }
        }
    }
}
