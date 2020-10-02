import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Start Remote Control Application")
    message:  qsTr("Start <b>%1</b> to be able to control MellowPlayer playback<br> from any device in your LAN!").arg(RemoteControlViewModel.appInfo.name)
    icon: MaterialIcons.icon_launch
    buttonText: qsTr("Start ") + RemoteControlViewModel.appInfo.name
    autoStartCheckBoxVisible: true

    onButtonClicked: RemoteControlViewModel.start()
}
