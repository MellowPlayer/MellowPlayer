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

// The two functions below can be used to control playback position and volume level
// See https://www.martin-brennan.com/simulating-mouse-click-event-javascript/ , 
// https://developer.mozilla.org/en-US/docs/Web/API/Element/getBoundingClientRect
// and https://developer.mozilla.org/en-US/docs/Web/API/MouseEvent for details
/**
 * @param element    (HTMLElement) Element to send events to. 
 * @param eventName  (String) type of the MouseEvent to send. 
 * @param relativeX  (Float) relative x position within the boundaries of the element, 
 * as a fraction of the element's width(0..1). 
 * @param relativeY  (Float) relative y position within the boundaries of the element,
 * as a fraction of the element's height(0..1).
*/

function sendMouseEventToElement(element, eventName, relativeX, relativeY) {
    var clientRect = element.getBoundingClientRect();
    var event = new MouseEvent(eventName, {
        'view': window,
        'bubbles': true,
        'cancelable': true,
        'clientX': clientRect.left + (clientRect.width * relativeX),
        'clientY': clientRect.top + (clientRect.height * relativeY)
    });
    element.dispatchEvent(event);
}
/**
 * Emulates mouse click on the specified position of the given element
 * @param element    (HTMLElement) Element to send click to. 
 * @param relativeX  (Float) relative x position within the boundaries of the element, 
 * as a fraction of the element's width(0..1). 
 * @param relativeY  (Float) relative y position within the boundaries of the element,
 * as a fraction of the element's height(0..1).
*/
function sendMouseClickToElement(element, relativeX, relativeY) {
    sendMouseEventToElement(element, 'mouseenter', relativeX, relativeY);
    sendMouseEventToElement(element, 'mousedown', relativeX, relativeY);
    sendMouseEventToElement(element, 'click', relativeX, relativeY);
    sendMouseEventToElement(element, 'mouseup', relativeX, relativeY);
    sendMouseEventToElement(element, 'mouseleave', relativeX, relativeY);
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
        "playbackStatus": pauseButton ? mellowplayer.PlaybackStatus.PLAYING : mellowplayer.PlaybackStatus.PAUSED,
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
