import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Install Remote Control Application")
    message:  qsTr("Install <b>%1</b> to finish Remote Control Setup").arg(RemoteControl.appInfo.name)
    icon: MaterialIcons.icon_get_app
    buttonText: qsTr("Install ") + RemoteControl.appInfo.name
    versionMessage: qsTr("Require <a href=\"%3\">%1</a> <i>%2</i>").arg(RemoteControl.appInfo.name).arg(RemoteControl.appInfo.minimumRequiredVersion).arg(RemoteControl.appInfo.homePage)

    onButtonClicked: RemoteControl.install()
}
