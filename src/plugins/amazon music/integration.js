//-----------------------------------------------------------------------------
// All code come from https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/master/src/plugins/googleplaymusic
//-----------------------------------------------------------------------------


function getButtons() {
    return {
        playpause: document.getElementsByClassName("playButton").item(0),
        skip: document.getElementsByClassName("nextButton").item(0),
        back: document.getElementsByClassName("previousButton").item(0),
        like: document.getElementsByClassName("listViewStatusButtonInLibrary").item(0)
    };
}

function update() {
    var elm = getButtons().playpause;
    var playbackStatus;

    if (!elm || elm.className.indexOf("disabled)") != -1)
        playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    else if (elm.className.indexOf("playerIconPlay") != -1)
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;
    else
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;

    var artUrl = null;
    try {
        artUrl = document.querySelector(".albumArtWrapper .renderImage").src;
    } catch (e) {}

    var songTitle = null;
    try {
        songTitle = document.querySelector(".playbackControlsView .trackTitle a").title;
    } catch (e) {}

    var artistName = null;
    try {
        artistName = document.querySelector(".playbackControlsView .trackArtist a").title;
    } catch (e) {}

    var albumTitle = null;
    try {
        albumTitle = document.querySelector(".playbackControlsView .trackSourceLink a").title;
    } catch (e) {}

    var albumTitle = null;
    try {
        albumTitle = document.querySelector(".playbackControlsView .trackSourceLink a").title;
    } catch (e) {}

    var canGoNext;
        elm = getButtons().skip;
        if (!elm || elm.className.indexOf("disabled)") != -1)
            canGoNext = false;
        else
            canGoNext = true;
    var canGoPrevious;
        elm = getButtons().back;
        if (!elm || elm.className.indexOf("disabled)") != -1)
            canGoPrevious = false;
        else
            canGoPrevious = true;
    
    var isFavorite,canAddToFavorites;
        elm = document.querySelector(".rightControls .listViewStatusButtonInLibrary .stroke");
        if (!elm){
            isFavorite = false;
            canAddToFavorites = false;
        } else if (elm.className.indexOf("added") != -1) {
            isFavorite = true;
            canAddToFavorites = true;
        } else {
            isFavorite = false;
            canAddToFavorites = true;
        }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": false,
        "canGoNext": canGoNext,
        "canGoPrevious": canGoPrevious,
        "canAddToFavorites": canAddToFavorites,
        "volume": 1,
        "duration": 0,
        "position": 0,
        "songId": getHashCode(songTitle),
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": albumTitle,
        "artUrl": artUrl,
        "isFavorite": isFavorite
    };
}

function play() {

    getButtons().playpause.click()

}

function pause() {

    getButtons().playpause.click()

}

function goNext() {

    getButtons().skip.click()

}

function goPrevious() {

    getButtons().back.click()

}

function setVolume(volume) {

    // not currently supported

}


function addToFavorites() {

    getButtons().like.click();

}

function removeFromFavorites() {

    getButtons().like.click();

}

function seekToPosition(position) {
    // not currently supported 
}
