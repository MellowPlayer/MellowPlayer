
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Remote Control Disabled")
    message: qsTr("Enable Remote Control to be able to control MellowPlayer playback\n from any device in your LAN!")
    icon: MaterialIcons.icon_phonelink_off
    footerVisible: false
    buttonText: qsTr("Enable Remote Control")

    onButtonClicked: _remoteControl.activate()
}