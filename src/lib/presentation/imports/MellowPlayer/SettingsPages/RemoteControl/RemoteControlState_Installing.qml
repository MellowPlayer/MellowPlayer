import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Installing Remote Control Application")
    message: qsTr("Installing <b>%1</b>. Please wait,\nthis may take a few minutes...").arg(_remoteControl.appInfo.name)
    icon: MaterialIcons.icon_get_app
    buttonVisible: false
    busyIndicatorVisible: true
    versionMessage: qsTr("Require <b>%1</b> <i>%2</i>").arg(_remoteControl.appInfo.name).arg(_remoteControl.appInfo.minimumRequiredVersion)
}
