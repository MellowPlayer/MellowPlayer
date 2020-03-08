var previousID = -1;
var previousState = -100;

function getItemByTestID(buttonName, parent) {
    parent = parent || document;
    return parent.querySelector("[data-test=\""+buttonName+"\"]");
}

function isPaused() {
    return getItemByTestID("play");
}

function getAlbumTitle(infoTable) {
    var links = infoTable.getElementsByTagName('a');
    for(var link = 0; link < links.length; link++)
        if(links[link].href.indexOf("/album/") !== -1)
            return links[link].innerHTML;
    return "";
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
    var results = {
        "playbackStatus": MellowPlayer.PlaybackStatus.STOPPED,
        "canSeek": false,
        "canGoNext": false,
        "canGoPrevious": false,
        "canAddToFavorites": false,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": 0,
        "songTitle": '',
        "artistName": '',
        "albumTitle": '',
        "artUrl": '',
        "isFavorite": false
    };

    // Check for progress bar to see if the player is loaded
    const progressBar = getItemByTestID("progress-bar");
    if(progressBar) {
        // Define constants
        // Select the footer player DOM element
        const infoDiv = getItemByTestID("footer-player");
        // Select the progres bar indicator to check if the song change occured
        const progressIndicator = progressBar.querySelector("div[class*='indicator']");
        // Select the SVG appearing when the player is loading
        const svgLoading = infoDiv.querySelector("svg[class*='isLoading']");
        // Select volume range element
        const volumeSlider = infoDiv.querySelector("input[class*='nativeRange']");
        // Select the favorite button
        const favoriteButton = infoDiv.querySelector("div[class*='mediaActions'] button[title*='Collection']");
        // Select the element containing the information about the track
        const infoTable = document.querySelector("div[class*='infoTable']");

        progressState = progressIndicator ? parseFloat(progressIndicator.style.transform.split("(")[1].split("%")[0]) : -100;

        results.songTitle = getItemByTestID("footer-track-title", infoDiv).children[0].innerHTML;
        results.songId = getHashCode(getItemByTestID("footer-track-title", infoDiv).children[0].href);
        
        results.playbackStatus = isPaused() ? MellowPlayer.PlaybackStatus.PAUSED : MellowPlayer.PlaybackStatus.PLAYING;
        // Check if the loading svg is present
        if(svgLoading) {
            results.playbackStatus = MellowPlayer.PlaybackStatus.BUFFERING;
            previousID = results.songId;
        };
        
        results.artUrl = getItemByTestID("current-media-imagery", infoDiv).children[0].src;
        
        // On the initial song, there is no buffering, so we can accept the first valid album art
        if(previousID == -1)
            previousID = results.songId;
        
        
        // We skip the default album image placeholder, it loads before the first album loads, so on start there won't
        // be a album on MPRIS as it will be cached for the first loaded song, also it doesn't show up as it is svg
        if(results.artUrl.indexOf("defaultAlbumImage.78c633.svg") !== -1)
            results.artUrl = "";

        // If the player is playing but the song has changed, check the progress
        // bar, because if it is running but the state is lower than before we
        // have missed the buffering event
        if(results.songId != previousID && progressState < previousState && progressState > -100) {
            previousID = results.songId;
        };

        // also don't allow to load the art if we still hasn't started buffering.
        // We drop the status about the song until we find the art, so it won't create multiple item in the listening history
        if(results.songId != previousID || results.playbackStatus == MellowPlayer.PlaybackStatus.BUFFERING) {
            results.songTitle = "";
            results.songId = 0;
            results.artUrl = "";
            
            return results;
        };

        results.canGoNext = !getItemByTestID("next", infoDiv).disabled;
        results.canGoPrevious = !getItemByTestID("previous", infoDiv).disabled;
        results.artistName = getItemByTestID("grid-item-detail-text-title-artist", infoDiv).innerHTML;
        // If it is paused, we use the seekbar's value, as if we seek, only that will be updated
        results.position = isPaused() ? progressBar.getAttribute("aria-valuenow") : toSeconds(getItemByTestID("duration", infoDiv).children[0].innerHTML);
        results.duration = toSeconds(getItemByTestID("duration", infoDiv).children[1].innerHTML);
        results.volume = volumeSlider.value / 100;
        results.isFavorite = favoriteButton.className.includes("favorite");
        results.albumTitle = getAlbumTitle(infoTable);
        results.canSeek = true;
        results.canAddToFavorites = true;

        // Save the progress state in the end
        previousState = progressState;
    };
    
    return results;
}

function play() {
    getItemByTestID("play").click();
}

function pause() {
    getItemByTestID("pause").click();
}

function goNext() {
    getItemByTestID("next").click();
}

function goPrevious() {
    getItemByTestID("previous").click();
}

function setVolume(volume) {
    if(volume == 0)
        getItemByTestID("volume", getItemByTestID("footer-player")).click();
    else{
        const volumeSlider = document.querySelector("div[data-test='footer-player'] input[class*='nativeRange']");
        volumeSlider.value = volume * 100;
        volumeSlider.dispatchEvent(new Event('input', {
            'bubbles': true
        }));
    }
}

function addToFavorites() {
    const favoriteButton = document.querySelector("div[class*='mediaActions'] button[title*='Collection']")
    favoriteButton.click();
}

function removeFromFavorites() {
    addToFavorites();
}

function seekToPosition(position) {
    var positionAsFraction = position / update().duration;   
    sendMouseClickToElement(getItemByTestID("interaction-layer", getItemByTestID("footer-player")), positionAsFraction, 0.5);   
}
