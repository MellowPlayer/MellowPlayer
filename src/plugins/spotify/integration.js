//-----------------------------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

function getButtons() {
    function getPlayPauseButton() {
        var playButton = document.querySelector('button[title=Play]');
        var pauseButton = document.querySelector('button[title=Pause]');

        if (playButton === null)
            return pauseButton;
        else
            return playButton;
    }

    function getSkipPreviousSongButton() {
        return document.querySelector('button[title=Previous]');
    }

    function getSkipNextSongButton() {
        return document.querySelector('button[title=Next]');
    }

    function getAddRemoveToMusicButton() {
        return document.querySelector('.now-playing > button');
    }

    return {
        "playPause": getPlayPauseButton(),
        "next": getSkipNextSongButton(),
        "previous": getSkipPreviousSongButton(),
        "addRemoveToMusic": getAddRemoveToMusicButton()
    };
}

function getPlaybackStatus() {
    var button = getButtons().playPause;
    if (button === null)
        return mellowplayer.PlaybackStatus.STOPPED;
    else if (button.title === "Play")
        return mellowplayer.PlaybackStatus.PAUSED;
    return mellowplayer.PlaybackStatus.PLAYING;
}

function getArtist() {
    try {
        return document.querySelector('.now-playing .track-info__artists').innerText;
    } catch (e) {
        return ""
    }
}

function getSongTitle() {
    try {
        return document.querySelector('.now-playing .track-info__name').innerText;
    } catch (e) {
        return ""
    }
}

function readTime(timeString) {
    var hours = 0;
    var minutes = 0;
    var seconds = 0;
    var m = timeString.match("\\d+:\\d+:\\d+");
    if (m !== null) {
        var data = timeString.split(':');
        hours = parseInt(data[0]);
        minutes = parseInt(data[1]);
        seconds = parseInt(data[2]);
    } else {
        var m = timeString.match("\\d+:\\d+");
        if (m !== null) {
            var data = timeString.split(':');
            minutes = parseInt(data[0]);
            seconds = parseInt(data[1]);
        }
    }
    return hours * 3600 + minutes * 60 + seconds;
}

function getPosition() {
    return readTime(document.querySelector('.playback-bar__progress-time:first-child').innerText);
}

function getDuration() {
    return readTime(document.querySelector('.playback-bar__progress-time:last-child').innerText);
}

function getVolume() {
    try {
        var value = parseFloat(document.querySelector('.volume-bar .progress-bar__fg').style.transform.replace("translateX(", "").replace("%)", ""))
        return (100.0 + value) / 100.0;
    } catch (e) {
        return 1;
    }
}

function getArtUrl() {
    var artUrlDiv = document.querySelector('.now-playing .cover-art-image.cover-art-image');
    if (artUrlDiv === null) {
        return "";
    }
    var artUrl = artUrlDiv.style.backgroundImage;
    return artUrl.replace('url("', '').replace('")', '');
}

function isFavorite() {
    var addRemoveToMusic = getButtons().addRemoveToMusic;
    if (addRemoveToMusic === null) {
        return false;
    }
    return addRemoveToMusic.attributes.class.value.match(".*active.*") !== null;
}

function update() {
    return {
        "songId": getHashCode(getSongTitle()).toString().replace("-", ""),
        "songTitle": getSongTitle(),
        "artistName": getArtist(),
        "albumTitle": "",
        "artUrl": getArtUrl(),
        "isFavorite": isFavorite(),
        "duration": getDuration(),
        "position": getPosition(),
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": getVolume()
    };
}

function play() {
    getButtons().playPause.click();
}

function pause() {
    getButtons().playPause.click();
}

function goNext() {
    getButtons().next.click();
}

function goPrevious() {
    getButtons().previous.click();
}

function setVolume(volume) {
    // not supported
}

function addToFavorites() {
    getButtons().addRemoveToMusic.click();
}

function removeFromFavorites() {
    getButtons().addRemoveToMusic.click();
}

function seekToPosition(position) {
    // not supported
}
