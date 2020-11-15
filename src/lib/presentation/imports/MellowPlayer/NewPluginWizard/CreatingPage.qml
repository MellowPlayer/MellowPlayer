import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

WizardPage {
    id: root

    property string svName
    property string svUrl
    property string authorName
    property string authorUrl
    property bool allPlatforms
    property bool linuxPlatform
    property bool osxPlatform
    property bool windowsPlatform

    property string directory: ""

    signal goNextRequested()

    title: qsTr("Creating plugin")
    description: qsTr("Please wait...")
    goBackVisible: false
    goNextVisible: true
    finishVisible: false
    goNextEnabled: !busyIndicator.running

    Component.onCompleted: {
        StreamingServicesViewModel.serviceCreated.connect((directory) => {
            root.directory = directory;
            root.goNextRequested();
        })
        StreamingServicesViewModel.createService(svName, svUrl, authorName, authorUrl, allPlatforms, linuxPlatform, osxPlatform, windowsPlatform)
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: root.directory == ""
    }
}
