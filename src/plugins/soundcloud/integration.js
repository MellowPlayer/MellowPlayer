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

function getPlaybackStatus() {
    var controlClassName = document.getElementsByClassName('playControl')[0].className;
    var playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;
    if (controlClassName.indexOf("playing") !== -1)
        playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
    else if (controlClassName.indexOf("disabled") !== -1)
        playbackStatus = MellowPlayer.PlaybackStatus.STOPPED;

    return playbackStatus;
}

function getArtUrl() {
    try {
        let artUrl = document.getElementsByClassName('playbackSoundBadge')[0].children[0].children[0].children[0].style["background-image"];
        return artUrl.replace('url("', "").replace('")', "").replace('50x50', '250x250');
    } catch (e) {
        return "";
    }
}

function getTitle() {
    try {
        return document.getElementsByClassName('playbackSoundBadge__titleLink')[0].title;
    } catch (e) {
        return '';
    }
}

function getArtist() {
    try {
        return document.getElementsByClassName('playbackSoundBadge__lightLink')[0].title;
    } catch (e) {
        return "";
    }
}

function readTime(elementClassName) {
    var html = document.getElementsByClassName(
        elementClassName)[0].innerHTML;
    var hours = 0;
    var minutes = 0;
    var seconds = 0;
    var m = html.match("<span .*>(\\d+:\\d+:\\d+)<\/span>");
    if (m !== null) {
        var data = m[1].split(':');
        hours = parseInt(data[0]);
        minutes = parseInt(data[1]);
        seconds = parseInt(data[2]);
    } else {
        var m = html.match("<span .*>(\\d+:\\d+)<\/span>");
        if (m !== null) {
            var data = m[1].split(':');
            minutes = parseInt(data[0]);
            seconds = parseInt(data[1]);
        }
    }
    return hours * 3600 + minutes * 60 + seconds;
}

function getPosition() {
    return readTime('playbackTimeline__timePassed');
}

function getDuration() {
    return readTime('playbackTimeline__duration');
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": 1,
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getTitle(),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getArtUrl(),
        "isFavorite": isFavorite()
    }
}

function isFavorite() {
    try {
        return document.getElementsByClassName('playbackSoundBadge__like')[0].title === "Unlike";
    } catch (e) {
        return false;
    }
}

function clickButton(buttonName) {
    document.getElementsByClassName(buttonName)[0].click()
}

function play() {
    clickButton('playControl');
}

function pause() {
    play();
}

function goNext() {
    clickButton('skipControl__next');
}

function goPrevious() {
    clickButton('skipControl__previous');
}

function addToFavorites() {
    clickButton('playbackSoundBadge__like');
}

function removeFromFavorites() {
    addToFavorites();
}

function setVolume(volume) {
    // not supported
}

function seekToPosition(position) {
    let positionSlider = document.getElementsByClassName('playbackTimeline__progressWrapper')[0];
    const duration = getDuration();
    sendMouseClickToElement(positionSlider, position / duration, 0.5);
}
