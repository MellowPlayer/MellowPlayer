function withExceptionHandler(func) {
    try {
        func();
    } catch (e) {
        MellowPlayer.player.broken = true;
        console.error(e);
    }
}


MellowPlayer = {
    ready: false,
    webChannel: null,
    player: null,
    refreshInterval: 100,
    refresh: function () {
        if (MellowPlayer.ready && MellowPlayer.player.isRunning) {
            withExceptionHandler(function() {
                var updateResults = update();
                try {
                    if (updateResults.songId == 0)
                        updateResults.songId = getHashCode(updateResults.songTitle);
                } catch (e) {
                    updateResults.songId = -1;
                }
                MellowPlayer.player.updateResults = updateResults;
            });
        }
    },
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
                MellowPlayer.player.seekToPosition.connect(function() { withExceptionHandler(seekToPosition); });
                MellowPlayer.player.changeVolume.connect(function() { withExceptionHandler(setVolume); });

                MellowPlayer.ready = true;
                window.setInterval(MellowPlayer.refresh, MellowPlayer.refreshInterval);
            });
        } catch (e) {
            console.warn(e);
        }
    }
};

MellowPlayer.initialize();
