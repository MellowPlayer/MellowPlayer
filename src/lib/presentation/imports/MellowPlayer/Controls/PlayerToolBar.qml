import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import MellowPlayer 3.0

Item {
    id: root

    clip: true

    RowLayout {
        id: layout

        anchors.fill: parent
        layoutDirection: Qt.RightToLeft
        visible: MainWindowViewModel.runningServices.model.count > 0 &&
                 SettingsViewModel.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value &&
                 ApplicationWindow.window.width > 767


        RowLayout {
            spacing: 0

            Layout.fillHeight: true


            IconToolButton {
                action: Actions.skipToPreviousSong
                iconChar: MaterialIcons.icon_fast_rewind
                tooltip: qsTr("Skip to previous song")
            }

            IconToolButton {
                action: Actions.playPause
                iconChar: CurrentPlayer.isPlaying ? MaterialIcons.icon_pause: MaterialIcons.icon_play_arrow
                tooltip: CurrentPlayer.isPlaying ? qsTr("Pause") : qsTr("Play")
            }

            IconToolButton {
                action: Actions.skipToNextSong
                iconChar: MaterialIcons.icon_fast_forward
                tooltip: qsTr("Skip to next song")
            }

            ToolSeparator { }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 128

            Label {
                text: getText()
                elide: "ElideRight"
                horizontalAlignment: Qt.AlignHCenter
                visible: width > 64

                anchors.left: parent.left
                anchors.right: parent.right
                y: (root.height - implicitHeight) / 2 - (sliderLayout.visible ? 6 : 0)

                function getText() {
                    var currentSong = CurrentPlayer.currentSong;
                    if (currentSong.title && currentSong.artist)
                        return "<b>" + currentSong.title.replace("&", "&amp;") + qsTr("</b><i> by ") + currentSong.artist.replace("&", "&amp;") + "</i>";
                    else if (currentSong.title)
                        return "<b>" + currentSong.title.replace("&", "&amp;") + "</b>";
                    return "";
                }
            }

            RowLayout {
                id: sliderLayout

                anchors.left: parent.left
                anchors.right: parent.right
                y: root.height / 4
                visible: slider.width > 32 && ( CurrentPlayer.canSeek && CurrentPlayer.currentSong.duration > 0 )

                Label {
                    text: {
                        var date = new Date(null);
                        date.setSeconds(CurrentPlayer.position); // specify value for SECONDS here
                        var text = date.toISOString().substr(11, 8);
                        try {
                            if (text.startsWith("00:"))
                                text = text.substr(3);
                        }
                        catch (TypeError) {

                        }
                        return text;
                    }
                    font.pixelSize: 10
                }

                Slider {
                    id: slider

                    padding: 0
                    hoverEnabled: !ApplicationViewModel.hasTouchScreen
                    from: 0; to: CurrentPlayer.currentSong.duration
                    value: CurrentPlayer.position

                    onMoved: {
                        if (CurrentPlayer.position !== value && CurrentPlayer.position < CurrentPlayer.currentSong.duration)
                            CurrentPlayer.seekToPosition(value)
                    }

                    Component.onCompleted: handle.visible = Qt.binding(() => CurrentPlayer.canSeek);
                    Layout.fillWidth: true
                    Material.accent: ThemeViewModel.accent === ThemeViewModel.primary ? ThemeViewModel.primaryForeground : ThemeViewModel.accent
                }

                Label {
                    text: {
                        var date = new Date(null);
                        date.setSeconds(CurrentPlayer.currentSong.duration - CurrentPlayer.position); // specify value for SECONDS here
                        var text = date.toISOString().substr(11, 8);
                        try {
                            if (text.startsWith("00:"))
                                text = text.substr(3);
                        }
                        catch (TypeError) {

                        }
                        return "-" + text;
                    }
                    font.pixelSize: 10
                }
            }
        }

        RowLayout {
            spacing: 0

            WebViewToolBar { }

            ToolSeparator { }

            IconToolButton {
                action: Actions.toggleFavoriteSong
                iconChar: CurrentPlayer.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border
                tooltip: CurrentPlayer.currentSong.isFavorite ? qsTr("Remove current song from your favorites") : qsTr("Add current song to your favorites")
                visible: SettingsViewModel.get(SettingKey.APPEARANCE_PLAYER_CONTROLS_VISIBLE).value

                Material.foreground: CurrentPlayer.currentSong.isFavorite ? ThemeViewModel.accent : ThemeViewModel.foreground
            }
        }
    }
}
