//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

// This latest version of PocketCasts' web player uses React and, thanks to the
// Brain.fm plugin, we can poke at the actual guts of the player.

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

function getPlayerState() {
    const el = document.querySelector("div.player-controls");
    if (!el) return null;
    return findReact(el);
}

function update() {
    const state = getPlayerState();
    let res = {
        playbackStatus: MellowPlayer.PlaybackStatus.STOPPED,
        canSeek: true,
        canGoNext: true,
        canGoPrevious: true,
        canAddToFavorites: false,
        volume: -1,
        duration: 0,
        position: 0,
        songId: -1,
        songTitle: "",
        artistName: "Brain.fm",
        albumTitle: "",
        artUrl: "",
        isFavorite: false,
    };

    if (state) {
        if (state.props.playing === true)
            res.playbackStatus = MellowPlayer.PlaybackStatus.PLAYING;
        else if (state.props.buffering === true)
            res.playbackStatus = MellowPlayer.PlaybackStatus.BUFFERING;
        else
            res.playbackStatus = MellowPlayer.PlaybackStatus.PAUSED;

        // See setVolume()
        res.volume = (res.volume == -1 ? 0 :
          (state.props.volume > 0.999 ? 0.999 : state.props.volume));

        if (state.props.episode) {
            res.duration = state.props.episode.duration;
            res.position = state.props.episode.playedUpTo;
            res.songId = state.props.episode.uuid;
            res.songTitle = state.props.episode.title;
            res.artistName = state.props.episode.podcastTitle;
            res.artUrl = "https://static.pocketcasts.com/discover/images/200/" +
                         state.props.episode.podcastUuid + ".jpg"
        }
    }

    return res;
}

function play() {
    getPlayerState().playClicked();
}

function pause() {
    getPlayerState().pauseClicked();
}

function goNext() {
    getPlayerState().skipForwardClicked();
}

function goPrevious() {
    getPlayerState().skipBackClicked();
}

function addToFavorites() {
    // not supported
}

function removeFromFavorites() {
    // not supported
}

function setVolume(volume) {
    // not supported -- tried to implement by making sure the volume is at least just short of 1, but MP won't show any
    // controls to adjust the volume.  I'm sure it's a floating point error somewhere.
    // getPlayerState().props.updateVolume(volume);
}

function seekToPosition(position) {
    getPlayerState().onUserSeeked(position);
}
