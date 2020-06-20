//ClassicalRadio.com

function getTitle() {
    try {
        return document.getElementsByClassName('track-name')[0].innerText.split('\n')[0];
    } catch(e) {
        return "";
    }
}

function getArtist() {
    try {
        return document.getElementsByClassName('artist-name')[0].innerText.replace(" - ");
    } catch(e) {
        return "";
    }
}

function getArtUrl() {
	try {
        return document.getElementsByClassName('wrap')[2].children[0].children[0].children[0].src;
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

function getPlaybackStatus() {
    if (document.querySelector('[data-state="playing"]'))
      return MellowPlayer.PlaybackStatus.PLAYING;
    else if (document.querySelector('[data-state="paused"]'))
      return MellowPlayer.PlaybackStatus.PAUSED;
    else if (document.querySelector('[data-state="connecting"]'))
      return MellowPlayer.PlaybackStatus.BUFFERING;
    else
      return MellowPlayer.PlaybackStatus.STOPPED;
}

function update() {
    return {
        "playbackStatus": getPlaybackStatus(),
        "canSeek": false,
        "canGoNext": true,
        "canGoPrevious": false,
        "canAddToFavorites": true,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": getSongId,
        "songTitle": getTitle(),
        "artistName": getArtist(),
        "albumTitle": '',
        "artUrl": getArtUrl(),
        "isFavorite": false
    };
}

function play() {
    document.querySelector("div[class*='ctl']").click();
}

function pause() {
    document.querySelector("div[class*='ctl']").click();
}

function goNext() {
    document.querySelector("a[class*='skip-btn']").click();
}

function goPrevious() {

}

function setVolume(volume) {

}

function addToFavorites() {
    document.querySelector("i[class*='icon icon-heart-empty']").click();
}

function removeFromFavorites() {
    document.querySelector("i[class*='icon icon-heart-empty']").click();
}

function seekToPosition(position) {

}
