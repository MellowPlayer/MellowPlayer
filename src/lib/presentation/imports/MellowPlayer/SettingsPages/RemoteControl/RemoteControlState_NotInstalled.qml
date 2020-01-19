import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Install Remote Control Application")
    message:  qsTr("Install <b>%1</b> to finish Remote Control Setup").arg(_remoteControl.appInfo.name)
    icon: MaterialIcons.icon_get_app
    buttonText: qsTr("Install ") + _remoteControl.appInfo.name
    versionMessage: qsTr("Require <a href=\"%3\">%1</a> <i>%2</i>").arg(_remoteControl.appInfo.name).arg(_remoteControl.appInfo.minimumRequiredVersion).arg(_remoteControl.appInfo.homePage)

    onButtonClicked: _remoteControl.install()
}
