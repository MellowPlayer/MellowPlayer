function getButtons() {
  return {
    playpause: document.querySelector(".js-play-pause"),
    next: document.querySelector(".js-next"),
    back: document.querySelector(".js-next"),
    favorite: document.querySelector(".js-love"),
    // thumbUp: document.querySelector('#player .player-rating-container [icon^="sj:thumb-"][data-rating="5"]'),
    // seekBar: document.getElementById('progressContainer')
  };
}

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
  var playbackStatus = MellowPlayer.PlaybackStatus.STOP;
  if (getButtons().playpause.classList.contains("player-bar-btn--pause") === true) {
    playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
  } else if (getButtons().playpause.classList.contains("player-bar-btn--play") === true) {
      playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;
  }

  return playbackStatus;
}

function update() {
  return {
    playbackStatus: getPlaybackStatus(),
    canSeek: false,
    canGoNext: goNext(),
    canGoPrevious: goPrevious(),
    canAddToFavorites: false,
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
  getButtons().back.click();
}

function setVolume(volume) {}

function addToFavorites() {}

function removeFromFavorites() {}

function seekToPosition(position) {}
