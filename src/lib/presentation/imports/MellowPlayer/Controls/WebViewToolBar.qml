import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import MellowPlayer 3.0

RowLayout {
    id: layout

    spacing: 0

    ToolSeparator { }

    IconToolButton {
        action: Actions.goBack
        iconChar: MaterialIcons.icon_chevron_left
        tooltip: qsTr("Go back")
    }

    IconToolButton {
        action: Actions.goForward
        iconChar: MaterialIcons.icon_chevron_right
        tooltip: qsTr("Go forward")
    }

    IconToolButton {
        action: Actions.reload
        iconChar: MaterialIcons.icon_refresh
        tooltip: qsTr("Reload page")
    }

    IconToolButton {
        action: Actions.goHome
        iconChar: MaterialIcons.icon_home
        tooltip: qsTr("Go to home page")
    }
}
