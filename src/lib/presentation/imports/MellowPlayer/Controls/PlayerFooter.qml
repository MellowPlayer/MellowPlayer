import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import MellowPlayer 3.0

ToolBar {
    id: root

    required property Drawer drawer

    Material.background: ThemeViewModel.secondary
    Material.foreground: ThemeViewModel.secondaryForeground
    Material.accent: ThemeViewModel.accent
    Material.theme: ThemeViewModel.isDark(ThemeViewModel.secondary) ?  Material.Dark : Material.Light

    Item {
        id: fakeDragTarget
        anchors.fill: parent

        DragHandler {
            target: fakeDragTarget
            xAxis.enabled: false
            grabPermissions: PointerHandler.TakeOverForbidden
            dragThreshold: 32

            onActiveChanged: if (active) {
                root.drawer.open()
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        IconToolButton {
            action: Actions.playPause
            iconChar: CurrentPlayer.isPlaying ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
            tooltip: CurrentPlayer.isPlaying ? qsTr("Pause") : qsTr("Play")
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 6
            spacing: 0

            Item { Layout.fillHeight: true }

            Label {
                text: CurrentPlayer.currentSong.title
                elide: "ElideMiddle"
                font.bold: true
                font.pixelSize: 14

                Layout.fillWidth: true
            }

            Label {
                text: CurrentPlayer.currentSong.artist + (CurrentPlayer.currentSong.album ? " - " + CurrentPlayer.currentSong.album : "")
                elide: "ElideMiddle"
                font.pixelSize: 12

                Layout.fillWidth: true
            }

            Item { Layout.fillHeight: true }
        }

        IconToolButton {
            action: Actions.toggleFavoriteSong
            iconChar: CurrentPlayer.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border
            tooltip: CurrentPlayer.currentSong.isFavorite ? qsTr("Remove current song from your favorites") : qsTr("Add current song to your favorites")
            visible: SettingsViewModel.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value

            Material.foreground: CurrentPlayer.currentSong.isFavorite ? ThemeViewModel.accent : ThemeViewModel.foreground
        }

        IconToolButton {
            action: Actions.skipToNextSong
            iconChar: MaterialIcons.icon_fast_forward
            tooltip: qsTr("Skip to next song")
        }
    }
}