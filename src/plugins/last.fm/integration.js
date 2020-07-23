function getButtons() {
    return {
        playpause: document.querySelector(".js-play-pause"),
        next: document.querySelector(".js-next"),
        previous: document.querySelector(".js-previous"),
        favorite: document.querySelector(".js-love"),
    };
}

function update() {
    return {
      playbackStatus: getPlaybackStatus(),
      canSeek: false,
      canGoNext: !getButtons().next.disabled,
      canGoPrevious: !getButtons().previous.disabled,
      canAddToFavorites: true,
      volume: 1,
      duration: getDuration(),
      position: getPosition(),
      songId: 0,
      songTitle: getTitle() ? getTitle().innerText : "",
      artistName: getArtist() ? getArtist().innerText : "",
      albumTitle: "",
      artUrl: getCover() ? getCover().src : undefined,
      isFavorite: isFavorite(),
    };
  }

function play() {
    getButtons().playpause.click();
}

function pause() {
    getButtons().playpause.click();
}

function goNext() {
    getButtons().next.click();
}

function goPrevious() {
    getButtons().previous.click();
}

function setVolume(volume) {}

function addToFavorites() {
    getButtons().favorite.click();
}

function removeFromFavorites() {
    getButtons().favorite.click();
}

function seekToPosition(position) {}

function getTitle() {
    return document.querySelector(".player-bar-track-name");
}

function getArtist() {
    return document.querySelector(".player-bar-artist-name");
}

function getCover() {
    return document.querySelector(".player-bar-artwork.js-artwork").children[0];
}

function isFavorite() {
    return getButtons().favorite.classList.contains("player-bar-btn--loved");
}

function getTime() {
    const timeRegExp = /(?:(\d\d?):)?(\d\d?):(\d\d)/;
    const html = document.querySelector(".js-progress-remaining").innerText;
    const match = html.match(timeRegExp);

    if (!match) return 0;

    const hours = parseInt(match[1]) || 0;
    const minutes = parseInt(match[2]) || 0;
    const seconds = parseInt(match[3]) || 0;

    return ((hours * 60) + minutes) * 60 + seconds;
}

let duration = 0;
function getDuration() {
    if (document.querySelector(".js-progress-slug").style.width < "0.1") {
        duration = getTime();
    }

    return duration;
}

function getPosition() {
    return duration - getTime();
}

function getPlaybackStatus() {
    let playbackStatus = MellowPlayer.PlaybackStatus.STOP;
    if (getButtons().playpause.classList.contains("player-bar-btn--pause") === true) {
        playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
    } else if (getButtons().playpause.classList.contains("player-bar-btn--play") === true) {
        playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;
    }

    return playbackStatus;
}
