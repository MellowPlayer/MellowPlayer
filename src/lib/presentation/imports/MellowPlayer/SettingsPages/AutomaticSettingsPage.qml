import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs
import "../Helpers/ModelHelpers.js" as ModelHelpers

ColumnLayout {
    id: root

    required property SettingListModel settings
    required property string categoryName

    ScrollView {
        contentHeight: listView.contentHeight
        clip: true

        Layout.fillHeight: true
        Layout.fillWidth: true

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

                width: listView.width
                spacing: 0

                required property string qmlComponent
                required property bool isEnabled
                required property string name
                required property string toolTip
                required property string type
                required property var value
                required property int index
                required property var model

                Loader {
                    id: loader

                    Layout.fillWidth: true
                    Layout.preferredHeight: 56
                }

                Rectangle {
                    color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
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
                        "qtObject": ModelHelpers.getQtObject(model)
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

            Material.foreground: ThemeViewModel.isDark(ThemeViewModel.accent) ? "white" : "#303030"

            Item { Layout.fillWidth: true }

            ToolButton {
                highlighted: true
                hoverEnabled: true
                text: qsTr("Restore defaults")

                onClicked: {
                    Dialogs.askConfirmation(
                        qsTr("Confirm restore defaults"),
                        qsTr("Are you sure you want to restore all %1 settings to their default values?").arg(root.categoryName),
                        (confirmed) => {
                            if (confirmed) {
                                SettingsViewModel.restoreCategoryDefaults(root.categoryName);
                            }
                        }
                    )
                }

                Tooltip {
                    text: qsTr('Restore <b>%1</b> settings to their <b>default values</b>.').arg(root.categoryName)
                }
            }
        }
    }
}
