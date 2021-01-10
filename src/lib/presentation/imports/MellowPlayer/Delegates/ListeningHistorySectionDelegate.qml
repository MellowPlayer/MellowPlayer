import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0
import "../Dialogs.js" as Dialogs
import "../DateCategoryTranslator.js" as DateCategoryTranslator

Pane {
    id: root

    required property string section
    property bool expanded: false

    signal toggleRequested()

    height: 64
    padding: 0

    Material.elevation: 2
    Material.background: ThemeViewModel.background
    Material.theme: ThemeViewModel.isDark(ThemeViewModel.background) ? Material.Dark : Material.Light

    ItemDelegate {
       anchors.fill: parent
       hoverEnabled: !ApplicationViewModel.hasTouchScreen
       padding: 0

       ColumnLayout {
           anchors.fill: parent
           anchors.leftMargin: parent.leftPadding
           anchors.rightMargin: parent.rightPadding
           anchors.topMargin: parent.topPadding
           anchors.bottomMargin: 0
           spacing: 0

           RowLayout {
               Layout.fillWidth: true
               spacing: 0

               Item {
                   Layout.fillWidth: true
                   Layout.margins: 12

                   RowLayout {
                       anchors.fill: parent
                       spacing: 8

                       Label {
                           text: root.expanded ? MaterialIcons.icon_keyboard_arrow_down : MaterialIcons.icon_keyboard_arrow_right
                           font.family: MaterialIcons.family
                           font.pixelSize: 22
                           verticalAlignment: "AlignVCenter"

                           Layout.fillHeight: true
                       }

                       Label {
                           text: DateCategoryTranslator.translate(root.section)
                           font.weight: Font.Bold
                           verticalAlignment: "AlignVCenter"

                           Layout.fillHeight: true
                           Material.foreground: ThemeViewModel.accent
                       }

                       Item {
                           Layout.fillWidth: true
                       }
                   }
               }

               ToolButton {
                   text: MaterialIcons.icon_delete
                   font.pixelSize: 16
                   font.family: MaterialIcons.family
                   hoverEnabled: !ApplicationViewModel.hasTouchScreen

                   onClicked: {
                       Dialogs.askConfirmation(
                             qsTr("Confirm remove"),
                             qsTr('Are you sure you want to remote history of ' + root.section + '?'),
                             (confirmed) => {
                                 if (confirmed)
                                     ListeningHistoryViewModel.removeByDateCategory(root.section)
                             }
                       );
                   }

                   Layout.fillHeight: true
               }
           }

           Rectangle {
               color: ThemeViewModel.accent
               width: parent.width
               height: 3

               Layout.fillWidth: true
           }
       }

       onClicked: root.toggleRequested()
    }
}
