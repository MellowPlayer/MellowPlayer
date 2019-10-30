// From https://stackoverflow.com/a/39165137/113325
function findReact(dom) {
    let key = Object.keys(dom).find(key=>key.startsWith("__reactInternalInstance$"));
    let internalInstance = dom[key];
    if (internalInstance == null) return null;

    if (internalInstance.return) { // react 16+
        return internalInstance._debugOwner
            ? internalInstance._debugOwner.stateNode
            : internalInstance.return.stateNode;
    } else { // react <16
        return internalInstance._currentElement._owner._instance;
    }
}

function getPlayer() {
    const el = document.querySelector("div[class*=index__wrapper]");
    if (!el) return null;
    return findReact(el);
}

function update() {
    const player = getPlayer();
    let res = {
        playbackStatus: mellowplayer.PlaybackStatus.STOPPED,
        canSeek: true,
        canGoNext: true,
        canGoPrevious: false,
        canAddToFavorites: false,
        volume: 1,
        duration: 0,
        position: 0,
        songId: -1,
        songTitle: "",
        artistName: "Brain.fm",
        albumTitle: "",
        artUrl: "",
        isFavorite: false,
    };

    if (player) {
        if (player.props.playStatus === "PLAYING")
            res.playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
        else if (player.props.playStatus === "PAUSED")
            res.playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

        res.volume = player.props.volume / 100.;
        res.duration = player.props.totalDuration / 1000;
        res.position = player.props.totalPosition / 1000;
        if (player.props.station)
            res.albumTitle = player.props.station.name;
        if (player.props.song) {
            res.songId = player.props.song.token;
            res.songTitle = player.props.song.name;
        }
    }

    return res;
}

function play() {
    getPlayer().props.play();
}

function pause() {
    getPlayer().props.pause();
}

function goNext() {
    getPlayer().skip();
}

function goPrevious() {
    // not supported
}

function addToFavorites() {
    // not supported
}

function removeFromFavorites() {
    // not supported
}

function setVolume(volume) {
    getPlayer().props.setVolume(100 * volume);
}

function seekToPosition(position) {
    const player = getPlayer(),
          duration = player.props.totalDuration / 1000,
          pct = 100 * position / duration;
    player.seek(pct);
}
