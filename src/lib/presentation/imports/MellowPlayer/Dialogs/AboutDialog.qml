import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQml 2.15

import MellowPlayer 3.0

Popup {
    id: popup

    padding: 20
    modal: true
    height: 340
    width: 340

    onVisibleChanged: if (!visible) btCredits.checked = false

    Material.accent: ThemeViewModel.accent === "#ffc107" ? ThemeViewModel.primary : ThemeViewModel.accent === ThemeViewModel.background ? ThemeViewModel.foreground : ThemeViewModel.accent

    ColumnLayout {
        anchors.fill: parent
        spacing: 8

        Item {
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent
                spacing: 12

                Image {
                    source: "qrc:/MellowPlayer/Presentation/icons/mellowplayer.png"
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    antialiasing: true

                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredHeight: 64
                }

                Label {
                    font.bold: true
                    font.pixelSize: 18
                    text: "MellowPlayer"

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    text: Qt.application.version

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    text: qsTr("Cloud music integration for your desktop")

                    Layout.alignment: Qt.AlignCenter
                }

                Link {
                    name: qsTr('Website')
                    url: 'https://colinduquesnoy.gitlab.io/MellowPlayer/'

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    text: qsTr("Copyright 2014-2020 Colin Duquesnoy")

                    Layout.alignment: Qt.AlignCenter
                }

                Label {
                    id: labelBuildInfo
                    font.italic: true
                    font.pixelSize: 10
                    text: ApplicationViewModel.buildInfo
                    wrapMode: "Wrap"
                    horizontalAlignment: Qt.AlignHCenter

                    Layout.fillWidth: true
                }
            }

            Item {
                id: creditsPane

                readonly property int yPos: parent.height

                x: 6
                height: 148; width: parent.width - 12

                Pane {
                    id: creditsPaneContent

                    anchors {
                        fill: parent
                        topMargin: 2
                        leftMargin: 2
                        rightMargin: 2
                        bottomMargin: 0  // hide bottom elevation
                    }
                    padding: 16

                    Material.elevation: 2

                    ScrollView {
                        anchors.fill: parent
                        clip: true

                        RowLayout {
                            anchors.fill: parent

                            Item {
                                Layout.fillWidth: true
                                Layout.minimumWidth: creditsPane.width / 2 - columnLayout.implicitWidth / 2 - creditsPaneContent.padding / 2 - creditsPaneContent.anchors.leftMargin / 2
                            }

                            ColumnLayout {
                                id: columnLayout

                                spacing: 9

                                RowLayout {
                                    spacing: 9

                                    Layout.fillWidth: true

                                    ColumnLayout {
                                        Layout.fillWidth: true

                                        Label {
                                            text: qsTr("Created by")
                                        }

                                        Item { Layout.fillHeight: true }
                                    }

                                    ColumnLayout {
                                        Layout.fillWidth: true

                                        Link {
                                            name: '@ColinDuquesnoy'
                                            url: "https://gitlab.com/ColinDuquesnoy"

                                            Layout.alignment: Qt.AlignHCenter
                                        }

                                        Item { Layout.fillHeight: true }
                                    }
                                }

                                RowLayout {
                                    spacing: 9

                                    Layout.fillWidth: true

                                    ColumnLayout {
                                        Layout.fillWidth: true

                                        Label {
                                            text: qsTr("Artwork by")
                                        }

                                        Item { Layout.fillHeight: true }
                                    }

                                    ColumnLayout {
                                        Layout.fillWidth: true

                                        Link {
                                            name: '@CelineThiry'
                                            url: "https://github.com/CelineThiry"
                                        }

                                        Item { Layout.fillHeight: true }
                                    }
                                }

                                RowLayout {
                                    spacing: 9

                                    Layout.fillWidth: true

                                    ColumnLayout {
                                        Label {
                                            text: qsTr("Contributors")
                                        }

                                        Item { Layout.fillHeight: true }
                                    }

                                    ColumnLayout {
                                        Link {
                                            name: '@ConorIA'
                                            url: "https://github.com/ConorIA"
                                        }

                                        Link {
                                            name: '@ZeroDot1'
                                            url: "https://gitlab.com/ZeroDot1"
                                        }

                                        Link {
                                            name: '@mahmoudhossam'
                                            url: "https://github.com/mahmoudhossam"
                                        }

                                        Link {
                                            name: '@kolletzki'
                                            url: "https://github.com/kolletzki"
                                        }

                                        Item { Layout.fillHeight: true }
                                    }
                                }
                            }

                            Item {
                                Layout.fillWidth: true
                            }
                        }
                    }
                }

                state: btCredits.checked && popup.visible ? "open" : "closed"
                states: [
                    State {
                        name: "open"

                        PropertyChanges {
                            target: creditsPane

                            y: creditsPane.yPos - creditsPane.height
                            clip: false
                        }
                    },
                    State {
                        name: "closed"

                        PropertyChanges {
                            target: creditsPane

                            y: creditsPane.yPos
                            clip: true
                        }
                    }
                ]

                transitions: Transition {
                    from: "open"; to: "closed"
                    reversible: true

                    PropertyAnimation {
                        properties: "y"
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                id: btCredits
                checkable: true
                checked: false
                flat: true
                text: qsTr("Credits")
            }

            Button {
                flat: true
                highlighted: true
                onClicked: ApplicationViewModel.showLogs()
                text: qsTr("Show logs")
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                flat: true
                highlighted: true
                onClicked: popup.close()
                text: qsTr("Close")
            }
        }
    }
}
