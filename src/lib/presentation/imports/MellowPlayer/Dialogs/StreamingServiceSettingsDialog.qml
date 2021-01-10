import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import QtQuick.Dialogs 1.2 as NativeDialogs
import QtQuick.Controls 1.2 as QuickControls1

import MellowPlayer 3.0
import "../SettingsPages"
import "../Dialogs.js" as Dialogs
import "../Helpers/ModelHelpers.js" as ModelHelpers
import "../Helpers/TabBarHelpers.js" as TabBarHelpers

Dialog {
    id: root

    property NullStreamingServiceViewModel nullService: NullStreamingServiceViewModel { }
    property StreamingServiceViewModel service: nullService

    clip: true
    modal: true
    title: root.service.name
    padding: 0; spacing: 0
    height: 460
    width: ApplicationWindow.window.width >= 490 ? 490 : ApplicationWindow.window.width

    Component.onCompleted: {
        tabBar.currentIndex = -1;
        tabBar.currentIndex = 0;
    }

    footer: RowLayout {
        Item {
            width: 12
        }

        RowLayout {
            spacing: 0

            Layout.alignment: Qt.AlignCenter
            Material.accent: ThemeViewModel.accent === "#ffc107" ? ThemeViewModel.primary : ThemeViewModel.accent

            Label {
                font.italic: true
                text: qsTr("Version ") + root.service.version + qsTr(" by ")
            }

            Link {
                font.italic: true
                name: root.service.authorName
                url: root.service.authorWebsite
            }
        }

        Item { Layout.fillWidth: true }

        Button {
            text: qsTr("Close")
            flat: true
            highlighted: true

            onClicked: root.close()

            Layout.rightMargin: 6
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 3
        spacing: 0
        clip: true

        ItemDelegateSeparator { Layout.fillWidth: true }

        TabBar {
            id: tabBar

            Layout.fillWidth: true
            Layout.preferredHeight: tabBar.implicitHeight
            Material.elevation: 4

            TabButton {
                text: "General"
                width: implicitWidth
            }

            TabButton {
                text: "User scripts"
                width: implicitWidth
            }

            TabButton {
                text: "Network Proxy"
                width: implicitWidth
            }

            TabButton {
                text: "Other options"
                visible: optionsListView.count > 0
                width: implicitWidth
            }
        }

        StackLayout {
            currentIndex: TabBarHelpers.getCurrentIndex(tabBar)

            Layout.fillWidth: true
            Layout.fillHeight: true

            Item {
                id: generalPage

                Layout.fillHeight: true
                Layout.fillWidth: true

                Pane {
                    anchors.fill: parent
                    padding: 0
                    width: parent.width / 2
                    height: parent.height * 0.75

                    Material.background: "transparent"


                    ColumnLayout {
                        spacing: 0
                        anchors.fill: parent

                        SwitchDelegate {
                            checked: root.service.notificationsEnabled
                            hoverEnabled: !ApplicationViewModel.hasTouchScreen
                            text: "Notifications"

                            onCheckedChanged: {
                                root.service.notificationsEnabled = checked
                            }

                            Layout.fillWidth: true
                        }

                        ItemDelegateSeparator { Layout.fillWidth: true }

                        TextFieldDelegate {
                            Layout.fillWidth: true
                            label: qsTr("URL: ")
                            value: root.service.url
                            onValueChanged: root.service.url = value
                        }

                        Item {
                            Layout.fillHeight: true
                        }
                    }
                }
            }

            StackLayout {
                id: userScripts
                currentIndex: root.service !== null && root.service.userScripts.hasScripts ? 1 : 0

                Layout.fillHeight: true
                Layout.fillWidth: true

                ColumnLayout {
                    spacing: 20

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Item {
                        Layout.fillHeight: true
                    }

                    Label {
                        text: MaterialIcons.icon_code
                        font.pixelSize: 64
                        font.family: MaterialIcons.family
                        color: Material.accent

                        horizontalAlignment: "AlignHCenter"

                        Layout.fillWidth: true
                    }

                    Label {
                        text: qsTr("No user script found")
                        font.bold: true
                        font.pixelSize: 20

                        horizontalAlignment: "AlignHCenter"

                        Layout.fillWidth: true
                    }

                    Button {
                        text: qsTr("Add user script")
                        highlighted: true
                        hoverEnabled: !ApplicationViewModel.hasTouchScreen
                        onClicked: root.showFileDialog()

                        Tooltip {
                            text: qsTr("Click to add a user script")
                        }

                        Layout.alignment: Qt.AlignCenter
                    }

                    Item {
                        Layout.fillHeight: true
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    ColumnLayout {
                        anchors.fill: parent

                        Pane {
                            id: userScriptListPane

                            padding: 0

                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Material.background: "transparent"

                            ScrollView {
                                id: scrollView

                                anchors.fill: parent

                                ScrollBar.horizontal.policy: "AlwaysOff"

                                ListView {
                                    id: listView

                                    anchors { fill: parent }
                                    model: root.service !== null ? root.service.userScripts.model : null
                                    spacing: 0
                                    clip: true

                                    remove: Transition {
                                        NumberAnimation { property: "x"; to: root.width; duration: 1 ; easing.type: Easing.InOutQuad }
                                    }
                                    removeDisplaced: Transition {
                                        NumberAnimation { properties: "x,y"; duration: 200; easing.type: Easing.InOutQuad }
                                    }

                                    delegate: ItemDelegate {
                                        id: userScriptDelegate

                                        required property int index
                                        required property string name

                                        onClicked: deleteToolButton.clicked()
                                        width: listView.width; height: 72
                                        hoverEnabled: !ApplicationViewModel.hasTouchScreen

                                        ListView.onRemove: SequentialAnimation {
                                            PropertyAction { target: userScriptDelegate; property: "ListView.delayRemove"; value: true }
                                            NumberAnimation { target: userScriptDelegate; property: "x"; to: root.width; duration: 200 ; easing.type: Easing.InOutQuad }
                                            PropertyAction { target: userScriptDelegate; property: "ListView.delayRemove"; value: false }
                                        }

                                        RowLayout {
                                            id: contentLayout

                                            anchors {
                                                left: parent.left
                                                right: parent.right
                                                verticalCenter: parent.verticalCenter
                                                leftMargin: parent.leftPadding
                                                rightMargin: parent.rightPadding
                                                topMargin: parent.topPadding
                                                bottomMargin: parent.bottomPadding
                                            }
                                            spacing: 16

                                            Label {
                                                text: MaterialIcons.icon_code
                                                font.pixelSize: 22
                                                font.family: MaterialIcons.family

                                                Material.foreground: ThemeViewModel.accent
                                            }

                                            Label {
                                                text: userScriptDelegate.name
                                                font.bold: true
                                            }

                                            Item {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                            }

                                            IconToolButton {
                                                id: deleteToolButton

                                                iconChar: MaterialIcons.icon_delete
                                                iconSize: 22
                                                tooltip: qsTr("Remove script")

                                                onClicked: {
                                                    Dialogs.askConfirmation(
                                                         qsTr("Confirm remove user script"),
                                                         qsTr('Are you sure you want to remove user script ') + userScriptDelegate.name + '?',
                                                         (confirmed) => {
                                                             if (confirmed)
                                                                 root.service.userScripts.remove(userScriptDelegate.name)
                                                         }
                                                    );
                                                }
                                            }
                                        }

                                        ItemDelegateSeparator {
                                            anchors { bottom: parent.bottom; left: parent.left; right: parent.right }
                                            visible: userScriptDelegate.index !== (listView.count - 1)
                                        }
                                    }
                                }
                            }
                        }

                        Pane {
                            padding: 0
                            Layout.fillWidth: true

                            ToolButton {
                                anchors.centerIn: parent
                                font { family: MaterialIcons.family; pixelSize: 24 }
                                flat: true
                                highlighted: true
                                hoverEnabled: !ApplicationViewModel.hasTouchScreen
                                text: MaterialIcons.icon_add

                                onClicked: root.showFileDialog()
                            }
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Pane {
                    id: networkProxyPane

                    padding: 0
                    anchors.fill: parent
                    width: parent.width / 2
                    height: parent.height * 0.75

                    Material.background: "transparent"


                    ColumnLayout {
                        anchors.fill: parent

                        SwitchDelegate {
                            id: networkProxySwitch
                            text: qsTr("Use custom network proxy")
                            checked: root.service.networkProxy.enabled
                            onCheckedChanged: root.service.networkProxy.enabled = checked

                            Layout.fillWidth: true
                        }

                        ItemDelegateSeparator { Layout.fillWidth: true }

                        TextFieldDelegate {
                            enabled: networkProxySwitch.checked
                            label: qsTr("Host")
                            value: root.service.networkProxy.hostName

                            onValueChanged: root.service.networkProxy.hostName = value

                            Layout.fillWidth: true
                        }

                        ItemDelegateSeparator { Layout.fillWidth: true }

                        SpinBoxDelegate {
                            label: qsTr("Port")
                            value: root.service.networkProxy.port
                            enabled: networkProxySwitch.checked
                            textFromValue: function(value, locale) { return value.toString(); }
                            valueFromText: function(text, locale) { return parseInt(text); }
                            onValueChanged: root.service.networkProxy.port = value

                            Layout.fillWidth: true
                        }

                        Item {
                            Layout.fillHeight: true
                        }

                        Pane {
                            visible: networkProxySwitch.checked

                            Layout.fillWidth: true
                            Material.background: Material.color(Material.Orange)
                            Material.foreground: "white"

                            RowLayout {
                                anchors.fill: parent
                                spacing: 12

                                Label {
                                    text: MaterialIcons.icon_warning
                                    font.family: MaterialIcons.family
                                    font.pixelSize: 32
                                    verticalAlignment: Text.AlignVCenter

                                    Layout.fillHeight: true
                                }

                                Label {
                                    font.pixelSize: 12
                                    text: qsTr("QtWebEngine does not support attaching a network proxy to a particular web view. The network proxy settings of the current streaming service are used globally, this may lead to some HTTP requests failurefor previously active services and you might need to reload them when you switch back.")
                                    wrapMode: Text.Wrap

                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Pane {
                    id: otherOptions

                    padding: 0
                    anchors.fill: parent
                    width: parent.width / 2
                    height: parent.height * 0.75

                    Material.background: "transparent"


                    ListView {
                        id: optionsListView

                        anchors.fill: parent
                        clip: true
                        delegate: ColumnLayout {
                            id: optionDelegate

                            required property string qmlComponent
                            required property bool isEnabled
                            required property string name
                            required property string toolTip
                            required property string type
                            required property var model
                            required property int index

                            width: root.width
                            spacing: 0

                            Loader {
                                id: loader

                                Layout.fillWidth: true
                                Layout.preferredHeight: 56
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

                            Rectangle {
                                color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
                                visible: optionDelegate.index !== optionsListView.count - 1

                                Layout.preferredHeight: 1
                                Layout.fillWidth: true
                            }
                        }
                        model: root.service.settings ? root.service.settings.settings : null
                        spacing: 0
                    }
                }
            }
        }

        Rectangle {
            color: ThemeViewModel.isDark(ThemeViewModel.background) ? Qt.lighter(ThemeViewModel.background) : Qt.darker(ThemeViewModel.background, 1.1)
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 1
            Layout.fillWidth: true
        }
    }

    function showFileDialog() {
        Dialogs.showFileDialog(
            [qsTr("Javascript files") + " (*.js)"],
            qsTr("Choose a user script"),
            (confirmed, fileUrl) => {
                if (confirmed) {
                    root.service.userScripts.add(root.service.userScripts.generateUniqueName(fileUrl), fileUrl)
                }
            }
        );
    }
}
