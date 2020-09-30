import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

ColumnLayout {
    id: root

    required property SettingListModel settings
    required property string categoryName

    ScrollView {
        contentHeight: listView.contentHeight
        contentWidth: width
        clip: true

        Layout.fillHeight: true
        Layout.fillWidth: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.vertical.size !== 1 ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded

        ListView {
            id: listView

            anchors {
                fill: parent;
                rightMargin: parent.ScrollBar.vertical.size != 1 ? 16 : 0
            }
            clip: true
            model: root.settings
            delegate: ColumnLayout {
                id: delegateRoot

                width: ListView.view.width
                spacing: 0

                required property string qmlComponent
                required property bool isEnabled
                required property string name
                required property string toolTip
                required property string type
                required property var model
                required property int index

                Loader {
                    id: loader

                    Layout.fillWidth: true
                    Layout.preferredHeight: 56
                }

                Rectangle {
                    color: ActiveTheme.isDark(ActiveTheme.background) ? Qt.lighter(ActiveTheme.background) : Qt.darker(ActiveTheme.background, 1.1)
                    visible: delegateRoot.index !== parent.ListView.view.count - 1

                    Layout.preferredHeight: 1
                    Layout.fillWidth: true
                }

                Component.onCompleted: {
                    var url = Qt.resolvedUrl("../" + qmlComponent)
                    var properties = {
                        "isEnabled": isEnabled,
                        "name": name,
                        "toolTip": toolTip,
                        "type": type,
                        "qmlComponent": qmlComponent,
                        "qtObject": model.qtObject
                    }

                    loader.setSource(url, properties)
                }
            }
            spacing: 0
        }
    }

    Pane {
        padding: 0
        Layout.fillWidth: true
        Material.elevation: 2

        RowLayout {
            anchors.fill: parent

            Material.foreground: ActiveTheme.isDark(ActiveTheme.accent) ? "white" : "#303030"

            Item { Layout.fillWidth: true }

            ToolButton {
                highlighted: true
                hoverEnabled: true
                text: qsTr("Restore defaults")

                onClicked: {
                    Dialogs.askConfirmation(
                        qsTr("Confirm restore defaults"),
                        qsTr("Are you sure you want to restore all %1 settings to their default values?").arg(root.categoryName.toLowerCase()),
                        (confirmed) => {
                            if (confirmed) {
                                App.settings.restoreCategoryDefaults(root.categoryName);
                            }
                        }
                    )
                }

                Tooltip {
                    text: qsTr('Restore <b>%1</b> settings to their <b>default values</b>.').arg(root.categoryName.toLowerCase())
                }
            }
        }
    }
}
