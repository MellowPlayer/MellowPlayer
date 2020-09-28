import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

import "../Dialogs.js" as Dialogs
import "../SettingsTranslator.js" as SettingsTranslator

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
            text: settingsPageList.currentCategory
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

                    ListView {
                        id: settingsPageList

                        property string currentCategory

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
                        delegate: ItemDelegate {
                            id: delegate

                            required property string name
                            required property int index
                            required property string iconName

                            property string category: SettingsTranslator.translateCategory(name)
                            property bool isCurrentItem: index === settingsPageList.currentIndex

                            height: 60; width: parent.width
                            hoverEnabled: true

                            onClicked: settingsPageList.currentIndex = index
                            onIsCurrentItemChanged: if (isCurrentItem) settingsPageList.currentCategory = category

                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: parent.leftPadding
                                anchors.rightMargin: parent.rightPadding
                                anchors.topMargin: parent.topPadding
                                anchors.bottomMargin: parent.bottomPadding

                                Label {
                                    text: delegate.iconName
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
                        }
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
                        onClicked: {
                            Dialogs.askConfirmation(
                                qsTr("Confirm restore defaults"),
                                qsTr("Are you sure you want to restore all settings to their default values?"),
                                (confirmed) => {
                                    if (confirmed) {
                                        App.settings.restoreDefaults();
                                    }
                                }
                            )
                        }

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
                    id: settingsPageLoader

                    required property string qmlComponent
                    required property SettingListModel settings
                    required property string name

                    width: parent.width
                    height: parent.height

                    Component.onCompleted: {
                        var url = Qt.resolvedUrl("../" + qmlComponent)
                        var properties = {
                            "categoryName": name,
                            "settings": settings
                        }
                        setSource(url, properties)
                    }
                }
            }
        }
    }
}
