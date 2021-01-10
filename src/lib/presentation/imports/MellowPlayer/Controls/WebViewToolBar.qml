import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import MellowPlayer 3.0

RowLayout {
    id: layout

    spacing: 0
    visible: MainWindowViewModel.runningServices.model.count > 0 && SettingsViewModel.get(SettingKey.APPEARANCE_WEBPAGE_CONTROLS_VISIBLE).value

    ToolSeparator {
        visible: ApplicationWindow.window.width > 767
    }

    IconToolButton {
        action: Actions.goBack
        iconChar: MaterialIcons.icon_chevron_left
        tooltip: qsTr("Go back")
        visible: ApplicationWindow.window.width > 767
    }

    IconToolButton {
        action: Actions.goForward
        iconChar: MaterialIcons.icon_chevron_right
        tooltip: qsTr("Go forward")
        visible: ApplicationWindow.window.width > 767
    }

    IconToolButton {
        action: Actions.reload
        iconChar: MaterialIcons.icon_refresh
        tooltip: qsTr("Reload page")
        visible: true
    }

    IconToolButton {
        action: Actions.goHome
        iconChar: MaterialIcons.icon_home
        tooltip: qsTr("Go to home page")
        visible: ApplicationWindow.window.width > 767
    }
}
