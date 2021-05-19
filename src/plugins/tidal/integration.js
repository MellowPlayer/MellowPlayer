function getTitle() {
    return navigator.mediaSession.metadata ? navigator.mediaSession.metadata.title : "";
}

function getSongId() {
    let songName = getTitle();
    if (songName != '') {
        return getHashCode(songName);
    }
    return '';
}

function getArtist() {
    return navigator.mediaSession.metadata ? navigator.mediaSession.metadata.artist : "";
}

function getAlbumTitle() {
    return navigator.mediaSession.metadata ? navigator.mediaSession.metadata.album : "";
}

function getArtUrl() {
    let artworks = navigator.mediaSession.metadata ? navigator.mediaSession.metadata.artwork : [];
    if (artworks.length > 0)
        return artworks[0].src;
    return '';
}

function getPosition() {
    try {
        position = document.querySelector('[data-test="current-time"]').innerText;
    } catch (e) {
        return 0;
    }
    return toSeconds(position);
}

function getDuration() {
    try {
        var time = document.querySelector('[data-test="duration-time"]').innerText;
    } catch (e) {
        return 0;
    }
    return toSeconds(time);
}

function isFavorite() {
    try {
        return document.querySelector('[data-test="footer-favorite-button"]').attributes['aria-checked'].value === 'true';
    } catch (e) {
        return false;
    }
}

function getPlaybackStatus() {
    if (navigator.mediaSession.playbackState === 'playing') {
        return MellowPlayer.PlaybackStatus.PLAYING;
    } else if (navigator.mediaSession.playbackState === 'paused') {
        return MellowPlayer.PlaybackStatus.PAUSED;
    } else {
        return MellowPlayer.PlaybackStatus.STOPPED;
    }
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": true,
        "canAddToFavorites": true,
        "volume": 1,
        "duration": getDuration(),
        "position": getPosition(),
        "songId": getSongId(),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": getAlbumTitle(),
        "artUrl": getArtUrl(),
        "isFavorite": isFavorite(),
    };
}

function play() {
    document.querySelector('[data-test="play"]').click();
}

function pause() {
    document.querySelector('[data-test="pause"]').click();
}

function goNext() {
    document.querySelector('[data-test="next"]').click();
}

function goPrevious() {
    document.querySelector('[data-test="previous"]').click();
}

function setVolume(volume) {

}

function addToFavorites() {
    document.querySelector('[data-test="footer-favorite-button"]').click();
}

function removeFromFavorites() {
    document.querySelector('[data-test="footer-favorite-button"]').click();
}

function seekToPosition(position) {

}
