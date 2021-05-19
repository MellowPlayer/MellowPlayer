function getTitle() {
    try {
        return document.querySelector('[data-test="footer-track-title"]').children[0].children[0].innerText;
    } catch (e) {
        return '';
    }
}

function getSongId() {
    var songName = getTitle();
    if (songName != '') {
        return getHashCode(songName);
    }
    return '';
}

function getArtist() {
    try {
        return document.querySelector('#footerPlayer [data-test="grid-item-detail-text-title-artist"]').innerText;
    } catch (e) {
        return '';
    }
}

function getAlbumTitle() {
    try {
        return document.querySelector('[data-test="left-column-footer-player"] [class*="container"] a').innerText;
    } catch (e) {
        return '';
    }
}

function getArtUrl() {
    try {
        return document.querySelector('[data-test="current-media-imagery"] img').src;
    } catch (e) {
        return '';
    }
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
    if (document.querySelector('[data-test="pause"]')) {
        return MellowPlayer.PlaybackStatus.PLAYING;
    } else if (document.querySelector('[data-test="play"]')) {
        return MellowPlayer.PlaybackStatus.PAUSED;
//    } else if (document.querySelector('[data-test="connecting"]')) {
//      return MellowPlayer.PlaybackStatus.BUFFERING;
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
