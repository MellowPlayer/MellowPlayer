import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0

Drawer {
    id: root

    clip: true
    edge: Qt.LeftEdge
    dragMargin: 0
    modal: true
    width: 400

    onVisibleChanged: searchToolButton.checked = false

    Page {
        anchors.fill: parent
        padding: 0

        header: ToolBar {
            Material.primary: ActiveTheme.primary
            Material.foreground: ActiveTheme.primaryForeground
            Material.elevation: 4
            Material.theme: ActiveTheme.isDark(ActiveTheme.primary) ? Material.Dark : Material.Light

            RowLayout {
                anchors.fill: parent

                IconToolButton {
                    action: Actions.toggleSelectServiceDrawer
                    iconChar: MaterialIcons.icon_keyboard_arrow_left
                    iconSize: 22

                    Layout.fillHeight: true

                    Tooltip {
                        text: qsTr("Back")
                    }
                }

                Item { Layout.fillWidth: true }

                IconToolButton {
                    id: searchToolButton

                    property bool previousFilterByFavoriteValue

                    iconChar: MaterialIcons.icon_search
                    iconSize: 22
                    checkable: true
                    checked: false

                    onCheckedChanged: {
                        if (checked) {
                            previousFilterByFavoriteValue = filterByFavorites.setting.value;
                            filterByFavorites.setting.value = false
                        }
                        else {
                            filterByFavorites.setting.value = previousFilterByFavoriteValue;
                        }
                    }

                    Layout.fillHeight: true

                    Tooltip {
                        text: qsTr("Search withing available services")
                    }
                }

                IconToolButton {
                    id: filterByFavorites

                    property SettingViewModel setting: App.settings.get(SettingKey.PRIVATE_SHOW_FAVORITE_SERVICES)

                    iconChar: MaterialIcons.icon_star
                    iconSize: 22
                    checkable: true
                    checked: setting.value
                    visible: !searchToolButton.checked

                    onToggled: setting.value = checked

                    Layout.fillHeight: true

                    Tooltip {
                        text: qsTr("Show only favorite services")
                    }
                }
            }

            Label {
                anchors.centerIn: parent
                text: qsTr("Select Streaming Service")
            }
        }

        ServicesOverview {
            anchors.fill: parent

            searchTextFieldVisible: searchToolButton.checked

            onServiceActivated: {
                console.log("Close select service drawer")
                root.close()
            }
        }
    }
}

