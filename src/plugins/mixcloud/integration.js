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
function getPlayPauseButton() {
    return getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[1]/div/span')
}

function getLoveButton() {
    return getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[4]/span/span');
}

function isPlaying() {
    let button = getPlayPauseButton();
    if (!button)
        return false;
    let svgPath = button.childNodes[0].childNodes[0];
    return !svgPath.getAttribute("d").endsWith("111z")
}

function getPlayInfoDiv() {
    return getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[3]');
}

function getTitle() {
    let label = getPlayInfoDiv().childNodes[0];
    if (label)
        return label.text;
    return "";
}

function getArtist() {
    let label = getPlayInfoDiv().childNodes[1].childNodes[1];
    if (label)
        return label.text;
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
    let artUrl = getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[2]/img');
    if (artUrl)
        return artUrl.src.replace("36x36", "512x512");
    return "";
}

function getPosition() {
    let label = getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[6]/div/div[1]/div[1]');
    if (label) {
        let text = label.innerHTML;
        return toSeconds(text);
    }
    return 0;
}

function getDuration() {
    let label = getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[6]/div/div[1]/div[2]');
    if (label) {
        let text = label.innerHTML.replace("-", "");
        let remainingTime = toSeconds(text);
        return remainingTime + getPosition();
    }
    return 0;
}

function getCloudCastQueue() {
    let element = getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[2]');
    if (element)
        return element.childNodes;
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
    if (getPlayInfoDiv()) {
        return {
            "playbackStatus": isPlaying() ? MellowPlayer.PlaybackStatus.PLAYING : MellowPlayer.PlaybackStatus.PAUSED,
            "canSeek": true,
            "canGoNext": isValidCloudCastIndex(getNextCloudCastIndex()),
            "canGoPrevious": isValidCloudCastIndex(getPreviousCloudCastIndex()),
            "canAddToFavorites": true,
            "volume": 1,
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

function togglePlayPause() {
    let button = getPlayPauseButton();
    if (button)
        button.click();
}

function play() {
    togglePlayPause();
}

function pause() {
    togglePlayPause();
}

function goNext() {
    getCloudCastQueue()[getNextCloudCastIndex()].childNodes[0].childNodes[0].click()
}

function goPrevious() {
    getCloudCastQueue()[getPreviousCloudCastIndex()].childNodes[0].childNodes[0].click()
}

function setVolume(volume) {

}

function toggleFavorite() {
    let button = getLoveButton();
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
    let positionSlider = getElementByXpath('//*[@id="react-root"]/div/section/div[5]/div/div/div[1]/div[6]/div/div[1]/div[3]');
    const duration = getDuration();
    sendMouseClickToElement(positionSlider, position / duration, 0.5);
}
