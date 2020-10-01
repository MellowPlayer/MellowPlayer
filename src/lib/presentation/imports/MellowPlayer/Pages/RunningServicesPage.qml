import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

StackLayout {
    id: root

    property WebView currentWebView: null
    onCurrentWebViewChanged: {
        console.debug("Current WebView: ", currentWebView ? currentWebView.service.name : "null")
    }

    currentIndex: MainWindow.runningServices.currentIndex + 1
    onCurrentIndexChanged: {
        if (currentIndex === 0)
            currentWebView = null;
    }

    function updateImages() {
        if (root.currentWebView)
            root.currentWebView.updateImage()
    }

    Action {
        id: goBack

        onTriggered: root.currentWebView.goBack()
        Component.onCompleted: Actions.goBack = goBack
    }

    Action {
        id: goForward

        onTriggered: root.currentWebView.goForward()
        Component.onCompleted: Actions.goForward = goForward
    }

    Action {
        id: goHome

        onTriggered: {
            console.warn("GoHome", root.currentWebView.url, root.currentWebView.service.url);
            root.currentWebView.url = "";
            root.currentWebView.url = root.currentWebView.service.url;
        }
        Component.onCompleted: Actions.goHome = goHome
    }

    Action {
        id: reload

        shortcut: App.settings.get(SettingKey.SHORTCUTS_RELOAD).value

        onTriggered: root.currentWebView.reload()
        Component.onCompleted: Actions.reload = reload
    }

    Shortcut {
        sequence: "Ctrl++"
        onActivated: root.currentWebView.zoomIn()
    }

    Shortcut {
        sequence: "Ctrl+-"
        onActivated: root.currentWebView.zoomOut()
    }

    Shortcut {
        sequence: "Ctrl+0"
        onActivated: root.currentWebView.resetZoom()
    }

    Shortcut {
        property Setting setting: App.settings.get(SettingKey.SHORTCUTS_SELECT_NEXT_SERVICE)

        sequence: setting.value
        onActivated: StreamingServices.next()
    }

    Shortcut {
        property Setting setting: App.settings.get(SettingKey.SHORTCUTS_SELECT_PREVIOUS_SERVICE)

        sequence: setting.value
        onActivated: StreamingServices.previous()
    }

    Item {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 32

        ColumnLayout {
            spacing: 0
            anchors.fill: parent

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Image {
                source: "qrc:/MellowPlayer/Presentation/icons/mellowplayer.png"
                fillMode: Image.PreserveAspectFit
                smooth: true
                antialiasing: true

                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredHeight: ApplicationWindow.window.width < 800 ? 96: 128
            }

            Label {
                text: qsTr("Welcome to MellowPlayer!")
                font.pixelSize: 24
                horizontalAlignment: Qt.AlignHCenter


                Layout.fillWidth: true
                Layout.topMargin: 24
            }

            Label {
                text: qsTr('There is no active streaming service, <b>choose one</b>!')
                horizontalAlignment: Qt.AlignHCenter

                Layout.fillWidth: true
                Layout.topMargin: 16
            }

            Pane {
                padding: 0

                Layout.fillWidth: true
                Layout.topMargin: 16

                Label {
                    id: arrowLabel

                    anchors.centerIn: parent

                    font.family: MaterialIcons.family
                    font.pixelSize: 18
                    text: MaterialIcons.icon_arrow_downward

                    SequentialAnimation {
                        id: bounceAnimation

                        loops: Animation.Infinite
                        running: true

                        PropertyAnimation {
                            target: arrowLabel
                            properties: "scale"
                            from: 1.0
                            to: 1.35
                            duration: 400
                        }

                        PropertyAnimation {
                            target: arrowLabel
                            properties: "scale"
                            from: 1.35
                            to: 1
                            duration: 400
                        }
                    }
                }
            }

            Pane {
                padding: 0
                Layout.fillWidth: true

                IconToolButton {
                    id: selectServiceButton

                    action: Actions.toggleSelectServiceDrawer
                    anchors.centerIn: parent
                    iconChar: MaterialIcons.icon_apps
                    iconSize: 24
                    tooltip: qsTr("Select another service")
                    scale: 1.5
                    highlighted: true
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        IconToolButton {
            action: Actions.openSettings
            iconChar: MaterialIcons.icon_settings
            iconSize: 24
            tooltip: qsTr("Open settings")
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 8
        }

        IconToolButton {
            action: Actions.quit
            iconChar: MaterialIcons.icon_power_settings_new
            iconSize: 24
            tooltip: qsTr("Open settings")
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 8
        }
    }

    Repeater {
        model: MainWindow.runningServices.model
        delegate: WebView {
            id: webView

            required property int index
            required property StreamingService qtObject
            property bool isCurrent: webView.index === root.currentIndex - 1

            service: qtObject
            onIsCurrentChanged: if (isCurrent) root.currentWebView = webView

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
