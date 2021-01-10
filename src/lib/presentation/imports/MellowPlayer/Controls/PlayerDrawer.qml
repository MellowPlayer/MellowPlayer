import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtWebEngine 1.10

import MellowPlayer 3.0

Drawer {
    id: root

    clip: true
    edge: Qt.BottomEdge
    modal: false
    interactive: ApplicationViewModel.hasTouchScreen && StreamingServicesViewModel.currentService
    height: ApplicationWindow.window.height
    width: ApplicationWindow.window.width

    onEnabledChanged: if (!enabled) close()

    Material.background: ThemeViewModel.secondary
    Material.foreground: ThemeViewModel.secondaryForeground
    Material.accent: ThemeViewModel.accent
    Material.theme: ThemeViewModel.isDark(ThemeViewModel.secondary) ?  Material.Dark : Material.Light

    ColumnLayout {
        anchors.fill: parent
        spacing: 6

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 48

            IconToolButton {
                anchors.top: parent.top
                anchors.left: parent.left
                iconChar: MaterialIcons.icon_keyboard_arrow_down
                iconSize: 22
                tooltip: qsTr("Back")

                onClicked: root.close()
            }

            Label {
                anchors.centerIn: parent
                text: StreamingServicesViewModel.currentService ? StreamingServicesViewModel.currentService.name : ""
                font.bold: true
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Pane {
            padding: 18

            Layout.fillHeight: true
            Layout.fillWidth: true

            Image {
                anchors.fill: parent
                source: CurrentPlayer.currentSong.artUrl ?
                    CurrentPlayer.currentSong.artUrl :
                    StreamingServicesViewModel.currentService ?
                        StreamingServicesViewModel.currentService.logo :
                        ""
                fillMode: Image.PreserveAspectFit
            }

            RoundButton {
                id: loveIcon

                anchors.centerIn: parent

                font { family: MaterialIcons.family; pixelSize: 24 }
                action: Actions.toggleFavoriteSong
                text: CurrentPlayer.currentSong.isFavorite ? MaterialIcons.icon_favorite : MaterialIcons.icon_favorite_border

                Layout.alignment: Qt.AlignHCenter
                Material.foreground: CurrentPlayer.currentSong.isFavorite ? ThemeViewModel.accent : ThemeViewModel.foreground

                background: Rectangle {
                    implicitWidth: 48
                    implicitHeight: 48
                    radius: implicitWidth
                    color: loveIcon.pressed ? "#40000000" : "#80000000"
                }
            }
        }



        Label {
            horizontalAlignment: Qt.AlignHCenter
            text: CurrentPlayer.currentSong.title
            font.pixelSize: 14
            font.bold: true

            Layout.fillWidth: true
        }

        Label {
            horizontalAlignment: Qt.AlignHCenter
            text: CurrentPlayer.currentSong.artist + (CurrentPlayer.currentSong.album ? " - " + CurrentPlayer.currentSong.album : "")
            font.pixelSize: 12

            Layout.fillWidth: true
        }

        RowLayout {
            spacing: 0

            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: sliderLayout.visible ? 0 : 32

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
        }

        RowLayout {
            id: sliderLayout
            visible: CurrentPlayer.canSeek && CurrentPlayer.currentSong.duration > 0

            Layout.fillWidth: true
            Layout.leftMargin: 32
            Layout.rightMargin: 32

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
}