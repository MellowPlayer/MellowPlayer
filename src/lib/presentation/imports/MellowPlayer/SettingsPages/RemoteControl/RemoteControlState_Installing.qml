import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Installing Remote Control Application")
    message: qsTr("Installing <b>%1</b>. Please wait,\nthis may take a few minutes...").arg(RemoteControlViewModel.appInfo.name)
    icon: MaterialIcons.icon_get_app
    buttonVisible: false
    busyIndicatorVisible: true
    versionMessage: qsTr("Require <a href=\"%3\">%1</a> <i>%2</i>").arg(RemoteControlViewModel.appInfo.name).arg(RemoteControlViewModel.appInfo.minimumRequiredVersion).arg(RemoteControlViewModel.appInfo.homePage)
}
