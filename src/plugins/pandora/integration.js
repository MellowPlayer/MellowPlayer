const timeRegExp = /(?:(\d\d?):)?(\d\d?):(\d\d)/;
const getElement = id => document.querySelector(`[data-qa="${id}"]`);

function getSeconds(timeString) {
    const match = timeString.match(timeRegExp);
    if (!match) return 0;

    const hours = parseInt(match[1]) || 0;
    const minutes = parseInt(match[2]) || 0;
    const seconds = parseInt(match[3]) || 0;
    
    return ((hours * 60) + minutes) * 60 + seconds;
}

function update() {
    const pauseButton = getElement('pause_button');
    const positionSlider = document.querySelector('.TunerProgress');
    const nextButton = getElement('skip_button') || getElement('t3_skip_forward_button');
    const previousButton = getElement('t3_skip_back_button') || getElement('replay_button');
    const volumeSliderHandle = getElement('volume_slider_handle');
    const durationLabel = getElement('remaining_time');
    const positionLabel = getElement('elapsed_time');
    const songLabel = getElement('mini_track_title');
    const artistLabel = getElement('mini_track_artist_name');
    const image = getElement('mini_track_image');
    
    const volume = volumeSliderHandle ? volumeSliderHandle.getAttribute('aria-valuenow') / 100 : undefined;
    const duration = durationLabel ? getSeconds(durationLabel.innerText) : undefined;
    const position = positionLabel ? getSeconds(positionLabel.innerText) : undefined;
    const songId = songLabel ? songLabel.href.slice(songLabel.href.lastIndexOf('/') + 1) : undefined;

    const data = {
        "playbackStatus": pauseButton ? MellowPlayer.PlaybackStatus.PLAYING : MellowPlayer.PlaybackStatus.PAUSED,
        "canSeek": !!positionSlider,
        "canGoNext": !!nextButton,
        "canGoPrevious": !!previousButton,
        "canAddToFavorites": false,
        "volume": volume,
        "duration": duration,
        "position": position,
        "songId": songId,
        "songTitle": songLabel ? songLabel.innerText : undefined,
        "artistName": artistLabel ? artistLabel.innerText : undefined,
        "albumTitle": undefined,
        "artUrl": image ? image.src : undefined,
        "isFavorite": undefined
    };

    return data;
}

function play() {
    const playButton = getElement('play_button');
    playButton.click();
}

function pause() {
    const pauseButton = getElement('pause_button');
    pauseButton.click();
}

function goNext() {
    const nextButton = getElement('skip_button') || getElement('t3_skip_forward_button');
    nextButton.click();
}

function goPrevious() {
    const previousButton = getElement('t3_skip_back_button') || getElement('replay_button');
    previousButton.click();
}

function setVolume(volume) {
    const volumeSlider = document.querySelector('.VolumeSlider__ClickTracker');
    sendMouseClickToElement(volumeSlider, volume, 0.5);
}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {
    const durationLabel = getElement('remaining_time');
    const positionSlider = document.querySelector('.TunerProgress');
    
    const duration = durationLabel ? getSeconds(durationLabel.innerText) : undefined;
    if (!duration) return;

    sendMouseClickToElement(positionSlider, position / duration, 0.5);
}
