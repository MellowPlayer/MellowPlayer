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
    return document.getElementsByClassName("unlogged-btn-label").length !== 0;
}

function update() {
    var playbackStatus = MellowPlayer.PlaybackStatus.STOPPED;
    if (dzPlayer.isPlaying())
        playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
    else if (dzPlayer.isPaused())
        playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;
    else if (dzPlayer.isLoading())
        playbackStatus = MellowPlayer.PlaybackStatus.BUFFERING;

    return {
        "playbackStatus": playbackStatus,
        "canSeek": dzPlayer.control.canSeek(),
        "canGoNext": dzPlayer.getNextSong() !== null,
        "canGoPrevious": dzPlayer.getPrevSong() !== null,
        "canAddToFavorites": true,
        "volume": dzPlayer.volume,
        "position": dzPlayer.getPosition(),
        "duration": dzPlayer.getDuration(),
        "isFavorite": isFavorite(),
        "songId": dzPlayer.getSongId(),
        "songTitle": dzPlayer.getSongTitle(),
        "artistName": dzPlayer.getArtistName(),
        "albumTitle": dzPlayer.getAlbumTitle(),
        "artUrl": 'http://e-cdn-images.deezer.com/images/cover/' + dzPlayer.getCover() + '/250x250.jpg'
    }
}

function getLoveButton() {
    var buttons = document.getElementsByClassName("svg-icon-love-outline");
    // current track love button is now always the last love button on the page.
    return buttons[buttons.length - 1].parentElement;
}

function getLoveButtonSvg() {
    return getLoveButton().children[0];
}

function isFavorite() {
    try {
        return getLoveButtonSvg().className.baseVal.indexOf("is-active") !== -1
    }
    catch (e) {
        return false;
    }
}

function play() {
    if (isOnLoginPage())
        return;
    dzPlayer.control.play();
}

function pause() {
    if (isOnLoginPage())
        return;
    dzPlayer.control.pause();
}

function goNext() {
    if (isOnLoginPage())
        return;
    dzPlayer.control.nextSong();
}

function goPrevious() {
    if (isOnLoginPage())
        return;
    dzPlayer.control.prevSong();
}

function setVolume(volume) {
    if (isOnLoginPage())
        return;
    dzPlayer.control.setVolume(volume);
}

function addToFavorites() {
    getLoveButton().click();
}

function removeFromFavorites() {
    getLoveButton().click();
}

function seekToPosition(position) {
    if (isOnLoginPage())
        return;

    // (0 = beginning, 1 = end)
    var normalizedPos = position / dzPlayer.getDuration();
    dzPlayer.control.seek(normalizedPos)
}
