//-----------------------------------------------------------------------------
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
function update() {
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    if (MusicKit.getInstance().nowPlayingItem != undefined && MusicKit.getInstance().nowPlayingItem.isLoading)
        playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
    else if (MusicKit.getInstance().isPlaying)
        playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
    else if (!MusicKit.getInstance().isPlaying)
        playbackStatus = mellowplayer.PlaybackStatus.PAUSED;

    try {
        var songId = MusicKit.getInstance().nowPlayingItem.songId;
    } catch (e) {
        songId = 0;
    }

    try {
        var songTitle = MusicKit.getInstance().nowPlayingItem.title;
    } catch (e) {
        songTitle = '';
    }

    try {
        var artistName = MusicKit.getInstance().nowPlayingItem.artistName;
    } catch (e) {
        artistName = '';
    }
    
    try {
        var albumTitle = MusicKit.getInstance().nowPlayingItem.albumName;
    } catch (e) {
        albumTitle = '';
    }

    try {
        var artUrl = MusicKit.getInstance().nowPlayingItem.artworkURL.replace("{w}", "250").replace("{h}", "250");;
    } catch (e) {
        artUrl = '';
    }

    return {
        "playbackStatus": playbackStatus,
        "canSeek": playbackStatus === mellowplayer.PlaybackStatus.PLAYING || playbackStatus === mellowplayer.PlaybackStatus.PAUSED,
        "canGoNext": MusicKit.getInstance().queue.nextPlayableItem != undefined,
        "canGoPrevious": MusicKit.getInstance().queue.previousPlayableItem != undefined,
        "canAddToFavorites": false,
        "volume": MusicKit.getInstance().volume,
        "duration": MusicKit.getInstance().currentPlaybackDuration,
        "position": MusicKit.getInstance().currentPlaybackTime,
        "songId": songId,
        "songTitle": songTitle,
        "artistName": artistName,
        "albumTitle": albumTitle,
        "artUrl": artUrl,
        "isFavorite": false
    };
}

function play() {
    MusicKit.getInstance().play();
}

function pause() {
    MusicKit.getInstance().pause();
}

function goNext() {
    MusicKit.getInstance().skipToNextItem();
}

function goPrevious() {
    MusicKit.getInstance().skipToPreviousItem();
}

function setVolume(volume) {
    MusicKit.getInstance().volume = volume;
}

function addToFavorites() {

}

function removeFromFavorites() {

}

function seekToPosition(position) {
    MusicKit.getInstance().seekToTime(position);
}
