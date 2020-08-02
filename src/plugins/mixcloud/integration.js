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
function getLoveButton() {
    var nodes = document.querySelectorAll("span[class*='PlayerActionsFavoriteButton__PlayerFavoriteIcon");
    if (nodes) {
        return nodes[0];
    }
    return null;
}

function isPlaying() {
    var audio = document.querySelector("audio");
    if (audio) {
        return !audio.paused;
    }
    return false;
}

function getTitle() {
    let label = document.querySelectorAll("p[class*='PlayerControls__ShowTitle']")[0]
    if (label)
        return label.innerText;
    return "";
}

function getArtist() {
    let label = document.querySelectorAll("p[class*='PlayerControls__ShowOwner']")[0];
    if (label)
        return label.childNodes[1].innerText;
    return "";
}

function isFavorite() {
    if (getLoveButton()) {
        let svg = getLoveButton().childNodes[0];
        return getComputedStyle(svg).color === "rgb(243, 178, 166)";
    }
    return false;
}

function getArtUrl() {
    let artUrl = document.querySelectorAll("div[class^='PlayerControls__ShowPicture']")[0]
    if (artUrl)
        return artUrl.children[0].src.replace("36x36", "512x512");
    return "";
}

function getPosition() {
    var audio = document.querySelector("audio");
    if (audio) {
        return audio.currentTime;
    }
    return 0;
}

function getDuration() {
    var audio = document.querySelector("audio");
    if (audio) {
        return audio.duration;
    }
    return 0;
}

function getCloudCastQueue() {
    let elements = document.querySelectorAll("div[class*='playerQueue__UpNextArea")
    if (elements)
        return elements[0].childNodes;
    return [];
}

function getCurrentCloudCastIndex() {
    let cloudCastQueue = getCloudCastQueue();
    for (let i = 0; i < cloudCastQueue.length; ++i) {
        let cloudCastItem = cloudCastQueue[i];
        if (cloudCastItem.childNodes.length === 2)
            return i;
    }
    return -1;
}

function getPreviousCloudCastIndex() {
    return getCurrentCloudCastIndex() - 1;
}

function getNextCloudCastIndex() {
    return getCurrentCloudCastIndex() + 1;
}

function isValidCloudCastIndex(cloudCastIndex) {
    return cloudCastIndex >= 0 && cloudCastIndex < getCloudCastQueue().length;
}

function update() {
    var audio = document.querySelector("audio");
    if (audio) {
        return {
            "playbackStatus": isPlaying() ? MellowPlayer.PlaybackStatus.PLAYING : MellowPlayer.PlaybackStatus.PAUSED,
            "canSeek": true,
            "canGoNext": isValidCloudCastIndex(getNextCloudCastIndex()),
            "canGoPrevious": isValidCloudCastIndex(getPreviousCloudCastIndex()),
            "canAddToFavorites": true,
            "volume": audio.volume,
            "duration": getDuration(),
            "position": getPosition(),
            "songId": getTitle(),
            "songTitle": getTitle(),
            "artistName": getArtist(),
            "albumTitle": "",
            "artUrl": getArtUrl(),
            "isFavorite": isFavorite()
        };
    }

    return {}
}

function play() {
    var audio = document.querySelector("audio");
    if (audio) {
        audio.play();
    }
}

function pause() {
    var audio = document.querySelector("audio");
    if (audio) {
        audio.pause();
    }
}

function goNext() {
    getCloudCastQueue()[getNextCloudCastIndex()].childNodes[0].childNodes[0].click()
}

function goPrevious() {
    getCloudCastQueue()[getPreviousCloudCastIndex()].childNodes[0].childNodes[0].click()
}

function setVolume(volume) {
    var audio = document.querySelector("audio");
    if (audio) {
        audio.volume = volume;
    }
}

function toggleFavorite() {
    var button = getLoveButton();
    if (button)
        button.click();
}

function addToFavorites() {
    toggleFavorite();
}

function removeFromFavorites() {
    toggleFavorite();
}

function seekToPosition(position) {
    var audio = document.querySelector("audio");
    if (audio) {
        audio.currentTime = position;
    }
}
