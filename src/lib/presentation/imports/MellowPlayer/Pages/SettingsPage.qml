import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Page {
    id: settingsPage

    signal closeRequested()

    Material.accent: ActiveTheme.accent === ActiveTheme.background ? ActiveTheme.foreground : ActiveTheme.accent

    header: ToolBar {
        id: toolBar

        Material.primary: ActiveTheme.primary
        Material.foreground: ActiveTheme.primaryForeground
        Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

        RowLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                id: btBack

                font { family: MaterialIcons.family; pixelSize: 24 }
                hoverEnabled: true
                text: MaterialIcons.icon_keyboard_arrow_right
                onClicked: settingsPage.closeRequested()

                Tooltip {
                    y: toolBar.implicitHeight
                    text: qsTr("Back")
                }

                Shortcut {
                    sequence: App.settings.get(SettingKey.SHORTCUTS_SETTINGS)
                    onActivated: settingsPage.closeRequested()
                }
            }
        }

        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: settingsPageList.currentItem.category
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            color: ActiveTheme.secondary

            Layout.fillHeight: true
            Layout.maximumWidth: 324
            Layout.minimumWidth: 324

            Pane {
                padding: 0
                anchors.fill: parent

                Material.background: ActiveTheme.secondary
                Material.foreground: ActiveTheme.secondaryForeground
                Material.elevation: 4
                Material.accent: ActiveTheme.accent
                Material.theme: ActiveTheme.isDark(ActiveTheme.secondary) ? Material.Dark : Material.Light

                ColumnLayout {
                    anchors.fill: parent

                    Component {
                        id: settingsCategoryDelegate

                        ItemDelegate {
                            id: delegate

                            property string category: SettingsTranslator.translateCategory(model.name)

                            height: 60; width: parent.width
                            hoverEnabled: true

                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: parent.leftPadding
                                anchors.rightMargin: parent.rightPadding
                                anchors.topMargin: parent.topPadding
                                anchors.bottomMargin: parent.bottomPadding

                                Label {
                                    text: model.icon
                                    font.family: MaterialIcons.family
                                    font.pixelSize: 24
                                }

                                Label {
                                    verticalAlignment: "AlignVCenter"
                                    text: delegate.category
                                    font.pixelSize: 20
                                }

                                Item { Layout.fillWidth: true; }
                            }

                            onClicked: settingsPageList.currentIndex = index
                        }
                    }

                    ListView {
                        id: settingsPageList

                        highlight: Rectangle {
                            color: ActiveTheme.isDark(ActiveTheme.secondary) ? "#10ffffff" : "#10000000"

                            Rectangle {
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom

                                width: 4
                                color: ActiveTheme.accent
                            }
                        }
                        highlightMoveDuration: 200
                        model: App.settings.categories
                        delegate: settingsCategoryDelegate
                        interactive: false

                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    Button {
                        id: btRestoreDefaults

                        flat: true
                        highlighted: true
                        hoverEnabled: true
                        text: qsTr("Restore all to defaults")
                        onClicked: messageBoxConfirmRestore.open()

                        Layout.fillWidth: true
                        Layout.leftMargin: 4
                        Layout.rightMargin: 4

                        Tooltip {
                            text: qsTr('Restore all settings to their <b>default value</b>.')
                        }
                    }
                }
            }
        }

        StackLayout {
            clip: true
            currentIndex: settingsPageList.currentIndex

            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: App.settings.categories

                Loader {
                    source: Qt.resolvedUrl("../" + model.qmlComponent)

                    width: parent.width
                    height: parent.height
                }
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmRestore

        standardButtons: Dialog.Yes | Dialog.No
        message: qsTr("Are you sure you want to restore all settings to their default values?")
        title: qsTr("Confirm restore defaults")
        x: settingsPage.width / 2 - width / 2
        y: settingsPage.height / 2 - height / 2

        onAccepted: App.settings.restoreDefaults()
    }
}
