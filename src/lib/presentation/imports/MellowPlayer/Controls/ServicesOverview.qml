import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQml.Models 2.15

import MellowPlayer 3.0
import "../Helpers/ModelHelpers.js" as ModelHelpers

Item {
    id: root

    signal serviceActivated()

    property alias searchTextFieldVisible: searchTextField.visible

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TextField {
            id: searchTextField

            placeholderText: qsTr("Search within available services")
            selectByMouse: true

            onTextChanged: StreamingServices.filteredServices.setSearchText(text)

            onVisibleChanged: {
                text= "";
                if (visible)
                    forceActiveFocus()
            }

            Layout.fillWidth: true
            Layout.margins: 16
        }

        Item {
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.bottomMargin: 16


            Item {
                anchors.fill: parent
                anchors.topMargin: 16
                anchors.leftMargin: 16

                GridView {
                    id: gridView

                    property bool dragActive: false
                    property int itemSpacing: 48

                    signal dropped()

                    anchors.centerIn: parent
                    focus: true
                    cellWidth: width / 2; cellHeight: cellWidth * (9/16) + 32
                    anchors.fill: parent

                    model: DelegateModel {
                        id: visualModel

                        Component.onCompleted: {
                            StreamingServices.filteredServices.update()
                            model = StreamingServices.filteredServices
                        }

                        delegate: Item {
                            id: delegateRoot

                            required property StreamingServiceViewModel qtObject

                            property int visualIndex: ModelHelpers.getItemsIndex(delegateRoot.DelegateModel)

                            width: gridView.cellWidth - gridView.itemSpacing / 2;
                            height: gridView.cellHeight - gridView.itemSpacing / 2

                            ServiceOverviewDelegate {
                                id: item

                                function updateIndex() { index = delegateRoot.visualIndex }

                                anchors { horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter }
                                height: gridView.cellHeight - 4; width: gridView.cellWidth - 4
                                service: delegateRoot.qtObject

                                onActivated: root.serviceActivated()

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

                                onEntered: ModelHelpers.moveItem(visualModel, delegateRoot, drag)
                            }
                        }
                    }

                    displaced: Transition {
                        NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
                    }

                    ScrollBar.vertical: ScrollBar {
                        id: scrollBar

                        hoverEnabled: true
                    }
                }
            }
        }
    }
}

