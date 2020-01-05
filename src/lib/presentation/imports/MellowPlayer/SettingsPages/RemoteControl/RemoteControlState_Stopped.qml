import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Start Remote Control Application")
    message:  qsTr("Start <b>%1</b> to be able to control MellowPlayer playback<br> from any device in your LAN!").arg(_remoteControl.appInfo.name)
    icon: MaterialIcons.icon_launch
    buttonText: qsTr("Start ") + _remoteControl.appInfo.name
    autoStartCheckBoxVisible: true

    onButtonClicked: _remoteControl.start()
}
