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
// Based in part on utils.js of Nuvolaruntime, which is:
//     Copyright 2014-2018 Jiří Janoušek <janousek.jiri@gmail.com> under the terms of BSD-2:
//     Redistribution and use in source and binary forms, with or without modification,
//     are permitted provided that the following conditions are met:
//     1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//     2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//     THIS SOFTWARE IS PROVIDED BY DMITRY VYUKOV "AS IS" AND ANY EXPRESS OR IMPLIED
//     WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//     MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//     SHALL DMITRY VYUKOV OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//     LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//     OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//     LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//     OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//     ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

var previousSongHash = "";
var updateInfoCache = {
    "playbackStatus": 0,
    "songId": 0,
    "songTitle": 0,
};

function update() {
    var controlClassName = document.getElementsByClassName('AudioVideoPlayerView-container-kWiFsz')[0];
    // if controlClassName is undefined the audioplayer isn't opened yet
    if (!controlClassName)
        return;
    var playbackStatus = MellowPlayer.PlaybackStatus.STOPPED;
    if (document.querySelector('button[data-qa-id=pauseButton]') !== null)
        playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
    else if (document.querySelector('button[data-qa-id=resumeButton]') !== null) {
        updateInfoCache["playbackStatus"] = MellowPlayer.PlaybackStatus.PAUSED;
        return updateInfoCache;
    }

    // We'll use this multiple times later on as it packs all the media info
    var mediaInfoElement = document.getElementsByClassName('PlayerControlsMetadata-container-2wqMfv')[0];

    try {
        var topElement = mediaInfoElement.children[0].title;
    } catch (e) {
        var topElement = '';
    }

    try {
        var middleLeftElement = mediaInfoElement.children[1].children[0].innerText;
    } catch (e) {
        var middleLeftElement = '';
    }
    if (middleLeftElement.match(/^\s*((S\d+\s*)?([·]\s*)?E\d+|\d+\/\d+\/\d+)\s*$/mg) !== null) {
        // Episodic or Date; Series is on the top
        try {
            var songTitle = mediaInfoElement.children[1].children[2].title;
        } catch (e) {
            var songTitle = '';
        }
        var artistName = topElement;
        var albumTitle = '';
    } else {
        var songTitle = topElement;
        try {
            var artistName = mediaInfoElement.children[1].children[0].innerText;
            var albumTitle = mediaInfoElement.children[1].children[2].title;
        } catch (e) {
            var artistName = '';
            var albumTitle = '';
        }
    }

    updateInfoCache = {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": mediaTime("duration"),
        "position": mediaTime("position"),
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": albumTitle,
//        "artUrl": artUrl,
    };

    return updateInfoCache;
}

function mediaTime(type) {
    var timeElement = document.getElementsByClassName("DurationRemaining-container-1F4w8F")[0]

    // if timeElement doesn't exist yet the site didn't finish loading yet
    if (!timeElement)
        return;
    else
        timeElement = timeElement.innerHTML;

    if (type === "position")
        // songPosition
        var time = timeElement.split(" / ")[0];
    else
        // songDuration
        var time = timeElement.split(" / ")[1];

    return toSeconds(time);
}

function clickButton(buttonName) {
    // Taken from: https://github.com/tiliado/nuvolaruntime/blob/master/src/mainjs/utils.js
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
        }
        opts.clientX = rect.left + width;
        opts.clientY = rect.top + height;
        opts.screenX = window.screenX + opts.clientX;
        opts.screenY = window.screenY + opts.clientY;
        var event = new MouseEvent(name, opts);
        elm.dispatchEvent(event);
    }

    function clickOnElement(elm, x, y) {
        triggerMouseEvent(elm, 'mouseover', x, y);
        triggerMouseEvent(elm, 'mousedown', x, y);
        triggerMouseEvent(elm, 'mouseup', x, y);
        triggerMouseEvent(elm, 'click', x, y);
    }

    clickOnElement(document.querySelector("button[data-qa-id=" + buttonName + "]"))
}

function play() {
    clickButton('resumeButton');
}

function pause() {
    clickButton('pauseButton');
}

function goNext() {
    clickButton('nextButton');
}

function goPrevious() {
    clickButton('previousButton');
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

