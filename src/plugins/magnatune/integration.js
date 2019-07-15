var pausedTiming = -1;

function update() {
    var playing = window.currently_playing || false;
    var current = currently_playing_info(playing);
    var playbackStatus = mellowplayer.PlaybackStatus.STOPPED;
    var current_volume = window.current_volume || 1;
    if (playing) {
        if (global_playState < 1 && sound_instances[currently_playing].position < 1000) {
            playbackStatus = mellowplayer.PlaybackStatus.BUFFERING;
        } else {
            playbackStatus = mellowplayer.PlaybackStatus.PLAYING;
        }
    }
    return {
        "playbackStatus": playbackStatus,
        "canSeek": playing,
        "canGoNext": playing,
        "canGoPrevious": playing,
        "canAddToFavorites": false,
        "volume": current_volume / 10.001,
        "duration": current['duration'],
        "position": current['position'],
        "songId": current['key'],
        "songTitle": current['title'],
        "artistName": current['artist'],
        "albumTitle": current['album'],
        "artUrl": current['cover'],
        "isFavorite": false
    };
}

function play() {
    play_song(0)
}

function pause() {
    var current = currently_playing_info();
    pausedTiming = (current && current['position']) || -1;
    stop_play();
}

function goNext() {
    play_next && play_next();
}

function goPrevious() {
    play_previous && play_previous();
}

function setVolume(volume) {
	// FIXME: no volume control gui
    current_volume = Math.round(volume * 10.001);
    if (current_volume > 10) {
        current_volume = 10
    }
    var instance = sound_instances[currently_playing];
    if (instance != undefined) {
        instance.setVolume(current_volume);
    }
    console.log("real volume: " + instance.volume)
    audio_controls_update(1);
}

function addToFavorites() {
    // TODO: implement
}

function removeFromFavorites() {
    // TODO: implement
}

function seekToPosition(position) {
    song_seek(position * 1000);
}


function currently_playing_info() {
    if (window.albumdata && currently_playing) {
        for (var songnum in albumdata.songs) {
            var music_key = albumdata.sku + ":" + songnum;
            if (music_key == currently_playing) {
                var position = sound_instances[currently_playing].position;
                return {
                    position: position / 1000.0,
                    duration: albumdata.songs[songnum].timing,
                    key: music_key,
                    title: albumdata.songs[songnum].desc,
                    artist: albumdata.artist,
                    album: albumdata.albumname,
                    cover: 'http://he3.magnatune.com/music/' +
                        encodeURIComponent(albumdata.artist) +
                        '/' + encodeURIComponent(albumdata.albumname) +
                        '/cover_400.jpg'
                };
            }
        }
    }
    return {
        position: 0,
        duration: 0,
        key: 0,
        title: '',
        artist: '',
        album: '',
        cover: '',
    };
}