function update() {
    if (document.getElementById('play-button').title == 'Pause')
        playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
    else
        playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;

    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": 0,
        "songTitle": document.getElementsByClassName('title')[0].innerText.split('\n')[0],
        "artistName": document.getElementsByClassName('artist')[0].innerText,
        "albumTitle": document.getElementsByClassName('album')[0].innerText,
        "artUrl": document.getElementsByClassName('now_playing_cover')[0].currentSrc,
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
