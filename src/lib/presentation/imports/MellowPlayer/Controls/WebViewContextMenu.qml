import QtQuick 2.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

Menu {
    id: root

    property bool canCopy: false
    property bool canPaste: false
    property bool canUnselect: false
    property bool canGoBack: false
    property bool canGoForward: false
    property bool hasLink: false

    signal copyRequested()
    signal pasteRequested()
    signal unselectRequested()
    signal copyLinkRequested()
    signal openLinkRequested()
    signal goBackRequested()
    signal goForwardRequested()
    signal reloadRequested()
    signal viewPageSourceRequested()
    signal openWebDeveloperTools()

    width: 250

    function show() {
        openTimer.running = true;
    }

    Timer {
        id: openTimer
        interval: 200
        onTriggered: root.open()
    }

    MenuItem { action: Actions.toggleToolBar }

    MenuSeparator { }

    MenuItem {
        height: visible ? implicitHeight : 0
        visible: root.canCopy
        text: qsTr("Copy")
        onClicked: root.copyRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Paste")
        visible: root.canPaste
        onClicked: root.pasteRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Unselect")
        visible: root.canUnselect
        onClicked: root.unselectRequested()
    }

    MenuSeparator {
        visible: root.canCopy || root.canPaste || root.canUnselect
        height: visible ? implicitHeight : 0
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Copy link")
        visible: root.hasLink
        onClicked: root.copyLinkRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Open link")
        visible: root.hasLink
        onClicked: root.openLinkRequested()
    }

    MenuSeparator {
        visible: root.hasLink
        height: visible ? implicitHeight : 0
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Back")
        visible: root.canGoBack
        onClicked: root.goBackRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Forward")
        visible: root.canGoForward
        onClicked: root.goForwardRequested()
    }

    MenuItem {
        height: visible ? implicitHeight : 0
        text: qsTr("Reload")
        onClicked: root.reloadRequested()
    }

    MenuItem {
        text: qsTr("View Page Source")
        onClicked: root.viewPageSourceRequested()
    }

    MenuItem {
        text: qsTr("Open web developer tools")
        onClicked: DevToolsWindow.show()
    }
}
