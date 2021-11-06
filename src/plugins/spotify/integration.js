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
        return document.querySelector('button[data-testid=control-button-playpause]');
    }

    function getSkipPreviousSongButton() {
        return document.querySelector('.player-controls__left button:last-child');
    }

    function getSkipNextSongButton() {
        return document.querySelector('button[data-testid=control-button-skip-forward]');
    }

    function getAddRemoveToMusicButton() {
        return document.querySelector('button[data-testid=add-button]');
    }

    return {
        "playPause": getPlayPauseButton(),
        "play": getPlayPauseButton(),
        "pause": getPlayPauseButton(),
        "next": getSkipNextSongButton(),
        "previous": getSkipPreviousSongButton(),
        "addRemoveToMusic": getAddRemoveToMusicButton()
    };
}

function getPlaybackStatus() {
    if (!getButtons().playPause)
      return MellowPlayer.PlaybackStatus.STOPPED;

    // When not playing, the title of the page always begins with "Spotify".
    // When playing, the title is the name of the song
    return  MellowPlayer.PlaybackStatus[/^Spotify/.test(document.title) ? "PAUSED" : "PLAYING"];
}

function getArtist() {
    return navigator.mediaSession.metadata ? navigator.mediaSession.metadata.artist : "";
}

function getSongTitle() {
    return navigator.mediaSession.metadata ? navigator.mediaSession.metadata.title : "";
}

function getArtUrl() {
    let artworks = navigator.mediaSession.metadata ? navigator.mediaSession.metadata.artwork : [];
    if (artworks.length > 0)
        return artworks[0].src;
    return "";
}

function getPlaybackPosition() {
  return toSeconds(document.querySelector('[data-testid=playback-position]').innerText);
}

function getPlaybackDuration() {
  return toSeconds(document.querySelector('[data-testid=playback-duration]').innerText);
}

function isFavorite() {
    var addRemoveToMusic = getButtons().addRemoveToMusic;
    if (addRemoveToMusic === null) {
        return false;
    }
    return addRemoveToMusic.getAttribute('aria-checked')
}

function update() {
    return {
        "songId": getHashCode(getSongTitle()).toString().replace("-", ""),
        "songTitle": getSongTitle(),
        "artistName": getArtist(),
        "albumTitle": "",
        "artUrl": getArtUrl(),
        "isFavorite": isFavorite(),
        "duration": getPlaybackDuration(),
        "position": getPlaybackPosition(),
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": getPlaybackStatus(),
        "canGoPrevious": getPlaybackStatus(),
        "canAddToFavorites": getPlaybackStatus(),
        "volume": 1
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

function setVolume(volume) {}

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

function seekToPosition(position) {}
