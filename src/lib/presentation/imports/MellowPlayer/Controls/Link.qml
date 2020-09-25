import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

Label {
    property string url: ""
    property string name: ""

    onLinkActivated: {
        console.log("opening external link: " + link);
        Qt.openUrlExternally(link)
    }
    text: '<a href="' + url + '">' + name + '</a>'

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
}
