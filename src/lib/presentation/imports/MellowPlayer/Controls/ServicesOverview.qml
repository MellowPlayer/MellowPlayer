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

            onTextChanged: StreamingServicesViewModel.filteredServices.setSearchText(text)

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

            Item {
                anchors.fill: parent
                anchors.leftMargin: 4

                ListView {
                    id: listView

                    property bool dragActive: false
                    signal dropped()

                    focus: true
                    anchors.fill: parent

                    model: DelegateModel {
                        id: visualModel

                        Component.onCompleted: {
                            StreamingServicesViewModel.filteredServices.update()
                            model = StreamingServicesViewModel.filteredServices
                        }

                        delegate: Item {
                            id: delegateRoot

                            required property StreamingServiceViewModel qtObject

                            property int visualIndex: ModelHelpers.getItemsIndex(delegateRoot.DelegateModel)

                            width: listView.width
                            height: item.height

                            ServiceOverviewDelegate {
                                id: item

                                function updateIndex() { index = delegateRoot.visualIndex }

                                width: listView.width - (scrollBar.size !== 1 ? 18 : 0)
                                height: 96
                                service: delegateRoot.qtObject

                                Drag.source: delegateRoot
                                Drag.hotSpot.x: width / 2
                                Drag.hotSpot.y: height / 2
                                Drag.onActiveChanged: {
                                    listView.dragActive = Drag.active
                                    if (!Drag.active)
                                        listView.dropped()
                                }

                                onActivated: root.serviceActivated()

                                Connections {
                                    target: listView

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
                                anchors.fill: parent

                                onEntered: {
                                    ModelHelpers.moveItem(visualModel, delegateRoot, drag)
                                }
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

