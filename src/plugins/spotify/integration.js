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

function isOnLoginPage() {
    return document.getElementsByClassName("login").length !== 0
}

function getButtons() {
    function getPlayPauseButton() {
        return document.querySelector('.Root__now-playing-bar button.spoticon-pause-16, .Root__now-playing-bar button.spoticon-play-16');
    }

    function getSkipPreviousSongButton() {
        return document.querySelector('.Root__now-playing-bar button.spoticon-skip-back-16');
    }

    function getSkipNextSongButton() {
        return document.querySelector('.Root__now-playing-bar button.spoticon-skip-forward-16');
    }

    function getAddRemoveToMusicButton() {
        return document.querySelector('.Root__now-playing-bar button.spoticon-heart-16, .Root__now-playing-bar button.spoticon-heart-active-16');
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
        return MellowPlayer.PlaybackStatus.STOPPED;
    else if (button.classList.contains("spoticon-play-16"))
        return MellowPlayer.PlaybackStatus.PAUSED;
    return MellowPlayer.PlaybackStatus.PLAYING;
}

function getArtist() {
    try {
        return document.querySelector('.Root__now-playing-bar .now-playing > div:nth-of-type(2) a[href^="/album/"]').innerText
    } catch (e) {
        return ""
    }
}

function getSongTitle() {
    try {
        return document.querySelector('.Root__now-playing-bar .now-playing a[href^="/artist/"]').innerText
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
    try {
        return readTime(document.querySelector('.playback-bar__progress-time:first-child').innerText);
    } catch (e) {
        return 0;
    }
}

function getDuration() {
    try {
        return readTime(document.querySelector('.playback-bar__progress-time:last-child').innerText);
    } catch (e) {
        return 0;
    }
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
    return addRemoveToMusic.classList.contains("spoticon-heart-active-16")
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
    if (isOnLoginPage())
        return;
    getButtons().playPause.click();
}

function pause() {
    if (isOnLoginPage())
        return;
    getButtons().playPause.click();
}

function goNext() {
    if (isOnLoginPage())
        return;
    getButtons().next.click();
}

function goPrevious() {
    if (isOnLoginPage())
        return;
    getButtons().previous.click();
}

function setVolume(volume) {
    // not supported
}

function addToFavorites() {
    if (isOnLoginPage())
        return;
    getButtons().addRemoveToMusic.click();
}

function removeFromFavorites() {
    if (isOnLoginPage())
        return;
    getButtons().addRemoveToMusic.click();
}

function seekToPosition(position) {
    if (isOnLoginPage())
        return;
}
