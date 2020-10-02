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

    font.pixelSize: width < 800 ? 14 : 16

    Material.accent: ThemeViewModel.accent === ThemeViewModel.background ? ThemeViewModel.foreground : ThemeViewModel.accent

    header: ToolBar {
        id: toolBar

        Material.primary: ThemeViewModel.primary
        Material.foreground: ThemeViewModel.primaryForeground
        Material.theme: ThemeViewModel.isDark(ThemeViewModel.primary) ? Material.Dark : Material.Light

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
                    sequence: SettingsViewModel.get(SettingKey.SHORTCUTS_SETTINGS)
                    onActivated: settingsPage.closeRequested()
                }
            }
        }

        Label {
            anchors.centerIn: parent
            font.pixelSize: settingsPage.width < 800 ? 16 : 18
            text: settingsPageList.currentCategory
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            color: ThemeViewModel.secondary

            property real minimumWidth: Math.max(Math.min(settingsPage.width / 3, 324), 192)

            Layout.fillHeight: true
            Layout.maximumWidth: minimumWidth
            Layout.minimumWidth: minimumWidth

            Pane {
                padding: 0
                anchors.fill: parent

                Material.background: ThemeViewModel.secondary
                Material.foreground: ThemeViewModel.secondaryForeground
                Material.elevation: 4
                Material.accent: ThemeViewModel.accent
                Material.theme: ThemeViewModel.isDark(ThemeViewModel.secondary) ? Material.Dark : Material.Light

                ColumnLayout {
                    anchors.fill: parent

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ListView {
                            id: settingsPageList

                            property string currentCategory

                            highlight: Rectangle {
                                color: ThemeViewModel.isDark(ThemeViewModel.secondary) ? "#10ffffff" : "#10000000"

                                Rectangle {
                                    anchors.top: parent.top
                                    anchors.left: parent.left
                                    anchors.bottom: parent.bottom

                                    width: 4
                                    color: ThemeViewModel.accent
                                }
                            }
                            highlightMoveDuration: 200
                            model: SettingsViewModel.categories
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
                                        font.pixelSize: 20
                                    }

                                    Label {
                                        verticalAlignment: "AlignVCenter"
                                        text: delegate.category
                                        font.pixelSize: settingsPage.width < 800 ? 16 : 18
                                    }

                                    Item { Layout.fillWidth: true; }
                                }
                            }
                        }
                    }

                    Pane {
                        padding: 0

                        Layout.fillWidth: true
                        Material.elevation: 2

                        Button {
                            id: btRestoreDefaults

                            anchors.fill: parent
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
                                            SettingsViewModel.restoreDefaults();
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
        }

        StackLayout {
            clip: true
            currentIndex: settingsPageList.currentIndex

            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: SettingsViewModel.categories

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
