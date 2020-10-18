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

var player;

var defaultArray = {
    "playbackStatus": 0,
    "volume": 0,
    "duration": 0,
    "position": 0,
    "songId": 0,
    "songTitle": "",
    "albumTitle": "",
    "artistName": "",
    "artUrl": "",
    "canSeek": false,
    "canGoNext": false,
    "canGoPrevious": false,
    "canAddToFavorites": false,
    "isFavorite": false
};

function update() {
    player = document.querySelector('video');

    // If the player is not currently playing a video
    if(!player) {
        return defaultArray;
    }

    // An ad is currently played
    var adContainer = document.getElementsByClassName('ytp-ad-skip-button-container')[0];
    if (adContainer) {

        // If the ad can't be skipped, the sound is muted
        if( adContainer.style.display == "none" ) {
            if (pluginSettings.muteAds)
                player.mute();

        // If the ad can be skipped, the sound is unmuted and the ad skipped
        } else if( document.getElementsByClassName('ytp-ad-skip-button')[0] ) {
            if (pluginSettings.skipAds)
                document.getElementsByClassName('ytp-ad-skip-button')[0].click();
            if (pluginSettings.muteAds)
                player.unMute();
        }
    }

    // Popup ads
    if (pluginSettings.closePopupAds) {
        var popupAdCloseButton = document.getElementsByClassName('ytp-ad-overlay-close-button')[0];
        if (popupAdCloseButton)
            popupAdCloseButton.click();
    }

    // Play progress
    const progressBar = document.querySelector('#progress-bar');
    let currentPosition;
    let totalDuration;
    if (progressBar) {
      currentPosition = parseInt(progressBar.getAttribute('aria-valuenow'), 10) || undefined;
      totalDuration = parseInt(progressBar.getAttribute('aria-valuemax'), 10) || undefined;
    }

    // Playback status
    if (player.paused) {
        var playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;
    } else {
        var playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
    }

    var songTitle = "", artistName = "", artUrl = "";

    // Song title
    try {
        var songTitle = document.querySelector('.title.ytmusic-player-bar').innerText;
    } catch (e) {
        var songTitle = "";
    }

    if(songTitle == "")
	    return defaultArray;

    var infos = document.querySelector('.subtitle.ytmusic-player-bar').children[0].children;

    var artistName = "";
    if (infos.length >= 1) {
        artistName = infos[0].innerText;
    }


    var albumTitle = "";
    if (infos.length >= 3) {
        albumTitle = infos[2].innerText;
    }



    // Art URL
    try {
        var artUrl = document.querySelector('img.ytmusic-player-bar').src;
    } catch (e) {
        var artUrl = "";
    }

    return {
        "playbackStatus": playbackStatus,
        "volume": player.volume,
        "duration": totalDuration,
        "position": currentPosition,
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "artUrl": artUrl,
        "canSeek": true,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "isFavorite": document.querySelector('.like.ytmusic-like-button-renderer').getAttribute("aria-pressed") == "true",
        "albumTitle": albumTitle
    };
}

function play() {
    player.play();
}

function pause() {
    player.pause();
}

function goNext() {
    document.querySelector('.next-button').click();
}

function goPrevious() {
    document.querySelector('.previous-button').click();
}

function setVolume(volume) {
    player.volume = volume;
}

function seekToPosition(position) {
    player.currentTime = position;
}

function addToFavorites() {
    document.querySelector('.like.ytmusic-like-button-renderer').click();
}

function removeFromFavorites() {
    document.querySelector('.like.ytmusic-like-button-renderer').click();
}
