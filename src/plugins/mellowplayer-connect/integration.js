function getPlaybackStatus() {
    return playerHub.playing ? MellowPlayer.PlaybackStatus.PLAYING : MellowPlayer.PlaybackStatus.PAUSED;
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": 0,
        "position": -1,
        "songId": currentSongHub.title,
        "songTitle": currentSongHub.title,
        "artistName": currentSongHub.artist,
        "albumTitle": currentSongHub.album,
        "artUrl": currentSongHub.artUrl,
        "isFavorite": currentSongHub.favorite
    };
}

function play() {
    playerHub.playPause();
}

function pause() {
    playerHub.playPause();
}

function goNext() {
    playerHub.next();
}

function goPrevious() {
    playerHub.previous();
}

function setVolume(volume) {

}

function addToFavorites() {
    currentSongHub.toggleFavorite();
}

function removeFromFavorites() {
    currentSongHub.toggleFavorite();
}

function seekToPosition(position) {
}
