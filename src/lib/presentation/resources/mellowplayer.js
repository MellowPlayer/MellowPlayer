/**
 * Wraps any function call with our exception handler that print the unhandled exception stack trace in the console
 * and mark the integration plugin as broken
 *
 * @param func Function to execute
 * @param args Function arguments
 */
function withExceptionHandler(func, ...args) {
    try {
        func(...args);
    } catch (e) {
        MellowPlayer.player.broken = true;
        console.error("Unhandled exception: " + e.stack);
    }
}

/**
 * The main MellowPlayer object, used to contain constants and to perform the bridge between QML and HTML/JS.
 */
MellowPlayer = {
    // Enums
    PlaybackStatus: {
        STOPPED: 0,
        PLAYING: 1,
        PAUSED: 2,
        BUFFERING: 3
    },
    // Working variables (private)
    ready: false,
    webChannel: null,
    player: null,
    refreshInterval: 100,

    // Refresh player information every 100 ms by default
    refresh: function () {
        if (MellowPlayer.ready && MellowPlayer.player.isRunning) {
            withExceptionHandler(function() {
                let updateResults = update();
                try {
                    updateResults.songId = getHashCode(updateResults.songTitle);
                } catch (e) {
                    updateResults.songId = -1;
                }
                MellowPlayer.player.updateResults = updateResults;
            });
        }
    },

    // Initialize connection with MellowPlayer's WebChannel
    initialize: function () {
        console.log("Connecting to MellowPlayer's WebChannel...");
        try {
            MellowPlayer.webChannel = new QWebChannel(qt.webChannelTransport, function (channel) {
                console.log("Connected to MellowPlayer's WebChannel, ready to send/receive messages!");

                MellowPlayer.player = channel.objects.player;

                // connect events to integration script functions
                MellowPlayer.player.play.connect(function() { withExceptionHandler(play); });
                MellowPlayer.player.pause.connect(function() { withExceptionHandler(pause); });
                MellowPlayer.player.next.connect(function() { withExceptionHandler(goNext); });
                MellowPlayer.player.previous.connect(function() { withExceptionHandler(goPrevious); });
                MellowPlayer.player.addToFavorites.connect(function() { withExceptionHandler(addToFavorites); });
                MellowPlayer.player.removeFromFavorites.connect(function() { withExceptionHandler(removeFromFavorites); });
                MellowPlayer.player.seekToPosition.connect(function(position) { withExceptionHandler(seekToPosition, position); });
                MellowPlayer.player.changeVolume.connect(function(volume) { withExceptionHandler(setVolume, volume); });

                MellowPlayer.ready = true;
                window.setInterval(MellowPlayer.refresh, MellowPlayer.refreshInterval);
            });
        } catch (e) {
            console.error("Connection to MellowPlayer's WebChannel failed: ", + e.stack);
        }
    }
};
MellowPlayer.initialize();

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions shared by many plugins
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Gets a dom NODE using an XPath
 *
 * @param path Path to get
 * @returns {Node} DOM node
 */
function getElementByXpath(path) {
    return document.evaluate(path, document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;
}

// The two functions below can be used to control playback position and volume level
// See https://www.martin-brennan.com/simulating-mouse-click-event-javascript/ ,
// https://developer.mozilla.org/en-US/docs/Web/API/Element/getBoundingClientRect
// and https://developer.mozilla.org/en-US/docs/Web/API/MouseEvent for details

/**
 * Sends a mouse move event to an HTMLElement
 *
 * @param element    (HTMLElement) Element to send events to.
 * @param eventName  (String) type of the MouseEvent to send.
 * @param relativeX  (Float) relative x position within the boundaries of the element,
 * as a fraction of the element's width(0..1).
 * @param relativeY  (Float) relative y position within the boundaries of the element,
 * as a fraction of the element's height(0..1).
 */
function sendMouseEventToElement(element, eventName, relativeX, relativeY) {
    let clientRect = element.getBoundingClientRect();
    let event = new MouseEvent(eventName, {
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
 *
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

/**
 * Converts a string to a hash code
 *
 * @param s string to hash
 * @returns {number} Hash code
 */
function getHashCode(s) {
    return s.split("").reduce(function(a, b) {
        a = ((a << 5) - a) + b.charCodeAt(0);
        return a & a
    }, 0);
}

/**
 * Converts a time string (HH:mm:ss) to a number of seconds
 *
 * @param string Time string to convert
 * @returns {number} Number of seconds
 */
function toSeconds(string) {
    let duration = 0;
    try {
        let dTimes = string.split(":");

        if (dTimes.length === 3) {
            let dHours = dTimes[0];
            let dMinutes = dTimes[1];
            let dSeconds = dTimes[2];
            duration = parseInt(dSeconds, 10) + (parseInt(dMinutes, 10) * 60) + (parseInt(dHours, 10) * 60 * 60);
        }
        else {
            let dMinutes = dTimes[0];
            let dSeconds = dTimes[1];
            duration = parseInt(dSeconds, 10) + (parseInt(dMinutes, 10) * 60);
        }
    } catch (e) {
        console.warn("failed to convert time string " + string + " to seconds, malformed input?", e.stack)
    }

    return duration
}