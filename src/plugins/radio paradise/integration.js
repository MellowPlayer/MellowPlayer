function getTitle() {
    try {
        return document.getElementsByClassName('title')[0].innerText.split('\n')[0];
    } catch(e) {
        return "";
    }
}

function getArtist() {
    try {
        return document.getElementsByClassName('artist')[0].innerText;
    } catch(e) {
        return "";
    }
}

function getAlbum() {
    try {
        return document.getElementsByClassName('album')[0].innerText;
    } catch(e) {
        return "";
    }
}

function getArtUrl() {
    try {
        return document.getElementsByClassName('now_playing_cover')[0].currentSrc;
    } catch(e) {
        return "";
    }
}

function getPlaybackStatus() {
    try {
        if (document.getElementById('play-button').title == 'Pause')
            return MellowPlayer.PlaybackStatus.PLAYING;
    } catch (e) { }
    return MellowPlayer.PlaybackStatus.PAUSED;
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": 0,
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": getAlbum(),
        "artUrl": getArtUrl(),
        "isFavorite": false
    };
}

function play() {
    document.getElementById("play-button").click();
}

function pause() {
    document.getElementById("play-button").click();
}

function goNext() {
    document.getElementById("skip-button").click();
}

function goPrevious() {
    // not supported;
}

function setVolume(volume) {
    // not implemeted;
}

function addToFavorites() {
    // not implemeted;
}

function removeFromFavorites() {
    // not implemeted;
}

function seekToPosition(position) {
    // not supported;
}
