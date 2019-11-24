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
function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

function getPlayerButtons() {
    return {
        play: document.querySelector('svg[data-testId="player-status-paused"]') || document.querySelector('svg[data-testId="player-status-stopped"]'),
        pause: document.querySelector('svg[data-testId="player-status-playing"]')
    };
}

function getPlayPauseButton() {
    var buttons = getPlayerButtons();
    console.log("buttons: " + buttons);
    return buttons.pause === null ? buttons.play : buttons.pause;
}

function getPlaybackStatus() {
    var buttons = getPlayerButtons();

    if (buttons.play === null && buttons.pause === null)
        return mellowplayer.PlaybackStatus.STOPPED;
    else if (buttons.play !== null)
        return mellowplayer.PlaybackStatus.PAUSED;
    else
        return mellowplayer.PlaybackStatus.PLAYING;
}

function getSongInfos() {
    try {
        return document.getElementById("playerTitle").innerText;
    } catch(e) {
        return "";
    }
}

function getArtist() {
    var tokens = getSongInfos().split("-");
    if (tokens.length > 2)
        return [0].trim();
    return "";
}

function getTitle() {
    var tokens = getSongInfos().split("-");
    if (tokens.length > 2)
        return getSongInfos().split("-")[1].trim();
    return getSongInfos();
}

function getArtUrl() {
    try {
        return document.getElementById("playerArtwork").src;
    } catch(e) {
        return "";
    }
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "songId": getHashCode(getTitle()),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getArtUrl(),
        "isFavorite": false,
        "duration": 0,
        "position": 0
    };
}

function triggerMouseEvent(elm, name, x, y) {
    var rect = elm.getBoundingClientRect();
    var width = rect.width * (x === undefined ? 0.5 : x);
    var height = rect.height * (y === undefined ? 0.5 : y);
    var opts = {
        view: document.defaultView,
        bubbles: true,
        cancelable: true,
        button: 0,
        relatedTarget: elm
    };
    opts.clientX = rect.left + width;
    opts.clientY = rect.top + height;
    opts.screenX = window.screenX + opts.clientX;
    opts.screenY = window.screenY + opts.clientY;
    var event = new window.MouseEvent(name, opts);
    elm.dispatchEvent(event)
}


function clickOnElement(elm, x=0.5, y=0.5) {
    triggerMouseEvent(elm, 'mouseover', x, y);
    triggerMouseEvent(elm, 'mousedown', x, y);
    triggerMouseEvent(elm, 'mouseup', x, y);
    triggerMouseEvent(elm, 'click', x, y);
    triggerMouseEvent(elm, 'mouseout', x, y);
}

function play() {
    clickOnElement(getPlayPauseButton())
}

function pause() {
    clickOnElement(getPlayPauseButton())
}

function goNext() {
    // not supported
}

function goPrevious() {
    // not supported
}

function setVolume(volume) {
    // not supported
}

function addToFavorites() {
    // not supported
}

function removeFromFavorites() {
    // not supported
}

function seekToPosition(position) {
    // not supported
}
