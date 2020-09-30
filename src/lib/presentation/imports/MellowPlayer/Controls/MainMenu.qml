import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Menu {
    implicitWidth: zoomMenuItem.implicitWidth
    spacing: 0

    IconMenuItem {
        iconChar: MaterialIcons.icon_settings
        action: Actions.openSettings
    }

    MenuItem {
        id: zoomMenuItem

        hoverEnabled: true
        padding: 0
        spacing: 0

        background: ColumnLayout {
            MenuSeparator { Layout.fillWidth: true }
            Item { Layout.fillHeight: true }
            MenuSeparator { Layout.fillWidth: true }
        }

        contentItem: RowLayout {
            spacing: 0

            Label {
                text: qsTr("Zoom")

                Layout.leftMargin: 16
            }

            ToolSeparator { Layout.fillHeight: true }

            SpinBox {
                id: zoomSpinBox

                padding: 0

                from: 50
                to: 300
                stepSize: 25
                value: MainWindow.zoom.value * 100

                onValueChanged: MainWindow.zoom.value = value / 100.0

                textFromValue:  function(value, locale) {
                    return Number(value).toLocaleString(locale, 'f', 0) + "%";
                }
            }

            ToolSeparator { Layout.fillHeight: true }

            Button {
                id: zoomResetButton

                text: MaterialIcons.icon_fullscreen
                font.family: MaterialIcons.family
                font.pixelSize: 22
                implicitWidth: 48
                flat: true

                onClicked: MainWindow.zoom.reset()

                Layout.rightMargin: 16
            }
        }
    }

    IconMenuItem {
        action: Actions.createNewPlugin
        iconChar: MaterialIcons.icon_extension
    }

    IconMenuItem {
        action: Actions.reportIssue
        iconChar: MaterialIcons.icon_bug_report
    }

    IconMenuItem {
        action: Actions.checkForUpdates
        iconChar: MaterialIcons.icon_update

        ProgressBar {
            anchors{ bottom: parent.bottom; horizontalCenter: parent.left; right: parent.right }
            indeterminate: Updater.progress === -1
            from: 0; to: 100
            value: Updater.progress
            visible: Updater.busy
        }
    }

    MenuSeparator { }

    IconMenuItem {
        action: Actions.showAbout
        iconChar: MaterialIcons.icon_info_outline
    }

    IconMenuItem {
        action: Actions.quit
        iconChar: MaterialIcons.icon_power_settings_new
    }
}
