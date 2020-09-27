import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQml.Models 2.15

import MellowPlayer 3.0

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: filtersLayout.implicitHeight
            Layout.topMargin: 24

            RowLayout {
                id: filtersLayout
                spacing: 0

                anchors.centerIn: parent
                implicitWidth: gridView.width

                Switch {
                    property var setting: App.settings.get(SettingKey.PRIVATE_SHOW_FAVORITE_SERVICES)

                    text: qsTr("Show only favorite services")
                    font.bold: true
                    checked: setting.value
                    onCheckedChanged: setting.value = checked

                }

                Item { Layout.fillWidth: true }


                TextField {
                    id: searchTextField

                    placeholderText: qsTr("Search within available services")
                    selectByMouse: true

                    onTextChanged: StreamingServices.filteredServices.setSearchText(text)

                    Component.onCompleted: {
                        StreamingServices.filteredServices.setSearchText(text)
                        forceActiveFocus()
                    }
                    Layout.preferredWidth: 340
                }
            }
        }

        Item {
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 32
            Layout.bottomMargin: 32

            Item {
                anchors.fill: parent
                anchors.leftMargin: 96
                anchors.rightMargin: 96
                anchors.topMargin: 12

                GridView {
                    id: gridView

                    property bool dragActive: false
                    property int itemSpacing: 48

                    signal dropped()

                    anchors.centerIn: parent
                    focus: true
                    cellWidth: 340; cellHeight: 192
                    height: parent.height
                    width: Math.floor(parent.width / cellWidth) * cellWidth

                    model: DelegateModel {
                        id: visualModel

                        Component.onCompleted: {
                            StreamingServices.filteredServices.update()
                            model = StreamingServices.filteredServices
                        }

                        delegate: Item {
                            id: delegateRoot

                            property int visualIndex: DelegateModel.itemsIndex
                            property var service: model.qtObject

                            width: gridView.cellWidth - gridView.itemSpacing / 2;
                            height: gridView.cellHeight - gridView.itemSpacing / 2

                            ServiceOverviewDelegate {
                                id: item

                                function updateIndex() { index = delegateRoot.visualIndex }

                                anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter }
                                height: gridView.cellHeight - 4; width: gridView.cellWidth - 4

                                Drag.source: delegateRoot
                                Drag.hotSpot.x: gridView.cellWidth / 2
                                Drag.hotSpot.y: gridView.cellHeight / 2
                                Drag.onActiveChanged: {
                                    gridView.dragActive = Drag.active
                                    if (!Drag.active)
                                        gridView.dropped()
                                }

                                Connections {
                                    target: gridView

                                    function onDropped () { item.index = delegateRoot.visualIndex }
                                }

                                states: State {
                                    when: item.Drag.active

                                    ParentChange {
                                        target: item
                                        parent: root
                                    }

                                    PropertyChanges {
                                        target: item
                                        z: 1
                                    }

                                    AnchorChanges {
                                        target: item;
                                        anchors.horizontalCenter: undefined;
                                        anchors.verticalCenter: undefined
                                    }
                                }
                            }

                            DropArea {
                                anchors { fill: parent; margins: 15 }

                                onEntered: {
                                    visualModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex)
                                }
                            }
                        }
                    }

                    displaced: Transition {
                        NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
                    }

                    ScrollBar.vertical: ScrollBar {
                        id: scrollBar
                        policy: size != 1 ? "AlwaysOn" : "AlwaysOff"
                        hoverEnabled: true
                    }
                }
            }
        }
    }
}

