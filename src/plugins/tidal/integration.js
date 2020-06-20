function getTitle() {
    try {
        return document.querySelector('[data-test="footer-track-title"]').children[0].innerHTML;
    } catch(e) {
        return "";
    }
}

function getSongId() {
	var songName = getTitle();
	if (songName != "") {
		return getHashCode(songName);
	}
	return ""
}

function getArtist() {
    try {
        return document.querySelector("div[class*='mediaArtists--3UIy']" ).innerText;
    } catch(e) {
        return "";
    }
}

function getAlbumTitle() {
    try {
        return document.querySelector("div[class*='container--UiaTi playingFrom--3x_p7']" ).children[1].children[0].innerHTML;
    } catch(e) {
        return "";
    }
}

function getArtUrl() {
	try {
        return document.querySelector('[data-test="current-media-imagery"]').children[0].children[0].src;
    } catch(e) {
        return "";
    }
}

function getPlaybackStatus() {
    if (document.querySelector('[data-test="pause"]'))
      return MellowPlayer.PlaybackStatus.PLAYING;
    else if (document.querySelector('[data-test="play"]'))
      return MellowPlayer.PlaybackStatus.PAUSED;
//    else if (document.querySelector('[data-test="connecting"]'))
//      return MellowPlayer.PlaybackStatus.BUFFERING;
    else
      return MellowPlayer.PlaybackStatus.STOPPED;
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
        "position": 0,
        "songId": getSongId(),
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": getAlbumTitle(),
        "artUrl": getArtUrl(),
        "isFavorite": false
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

}

function removeFromFavorites() {

}

function seekToPosition(position) {

}
