import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

ScrollView {
    id: root

    required property Drawer drawer
    property alias count: listView.count

    contentHeight: listView.contentHeight
    contentWidth: listView.contentWidth

    ListView {
        id: listView

        property var collapsed: ({})

        anchors {
            fill: parent
            rightMargin: root.ScrollBar.vertical.size != 1 ? 16 : 0
        }
        clip: true
        cacheBuffer: 500 * 72
        model: ListeningHistory.model
        delegate: ListeningHistoryEntryDelegate {
            view: listView
            expanded: listView.isSectionExpanded(dateCategory)
            drawer: root.drawer
        }
        section.criteria: ViewSection.FullString
        section.delegate: ListeningHistorySectionDelegate {
            width: listView.width
            expanded: listView.isSectionExpanded(section)
            onToggleRequested: listView.toggleSection(section)
        }
        section.property: "dateCategory"
        add: Transition {
            SequentialAnimation {
                NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
                PauseAnimation { duration: 100 }
                NumberAnimation { properties: "x"; duration: 200; from: 950; to: 0; easing.type: Easing.InOutQuad }
            }
        }
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200; easing.type: Easing.InOutQuad }
        }
        remove: Transition {
            NumberAnimation { property: "x"; to: 950; duration: 1 ; easing.type: Easing.InOutQuad }
        }
        removeDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 200; easing.type: Easing.InOutQuad }
        }

        function isSectionExpanded( section ) {
            return !(section in collapsed);
        }

        function showSection( section ) {
            delete collapsed[section]
            collapsedChanged();
        }

        function hideSection( section ) {
            collapsed[section] = true
            collapsedChanged();
        }

        function toggleSection( section ) {
            if ( isSectionExpanded( section ) ) {
                hideSection( section )
            } else {
                showSection( section )
            }
        }

        function expandAll() {
            collapsed = { }
            collapsedChanged()
        }
    }
}

