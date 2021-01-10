import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MellowPlayer 3.0

MenuItem {
    id: root

    property string iconChar
    property string shortcut

    hoverEnabled: !ApplicationViewModel.hasTouchScreen
    contentItem: RowLayout {
        spacing: 8

        Label {
            text: root.iconChar
            font { family: MaterialIcons.family; pixelSize: 22 }
        }

        Label {
            text: root.text
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            horizontalAlignment: "AlignRight"
            text: root.action.shortcut ?? ""
            font.italic: true

            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
            Layout.alignment: Qt.AlignRight
        }
    }
}
