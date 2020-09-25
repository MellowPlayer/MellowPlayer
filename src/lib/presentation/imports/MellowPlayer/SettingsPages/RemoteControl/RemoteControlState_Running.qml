import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

RemoteControlState {
    id: root

    title: qsTr("Remote Control Application Running")
    message:  qsTr("<b>%1</b> is listening on <a href=\"%2\">%2</a>").arg(_remoteControl.appInfo.name).arg(_remoteControl.appInfo.url)
    icon: MaterialIcons.icon_phonelink
    buttonText: qsTr("Stop ") + _remoteControl.appInfo.name
    buttonColor: Material.color(Material.Red, _theme.isDark(_theme.primary) ? Material.Shade600 : Material.Shade300)
    autoStartCheckBoxVisible: true

    onButtonClicked: _remoteControl.stop()
}
