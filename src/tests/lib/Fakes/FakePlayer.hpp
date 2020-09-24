#pragma once

#include <memory>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>

namespace MellowPlayer::Domain
{
    class FakePlayer : public IPlayer
    {
    private:
        int _trackIndex = -1;
        int _position = 0;
        double _volume;
        PlaybackStatus _playbackStatus{PlaybackStatus::Stopped};
        Song _fakeSong {
                "id",
                "title",
                "artist",
                "album",
                "https://fake.com/art-url.jpg",
                424242,
                true
        };
        Song* _currentSong { &_fakeSong };

    public:
        int trackIndex() const
        {
            return _trackIndex;
        }

        void setCurrentSong(Song* value)
        {
            if (_currentSong != value)
            {
                _currentSong = value;
                emit currentSongChanged(value);
            }
        }

        void setPlaybackStatus(PlaybackStatus value)
        {
            if (_playbackStatus != value)
            {
                _playbackStatus = value;
                emit playbackStatusChanged();
            }
        }

        void stop()
        {
            setPlaybackStatus(PlaybackStatus::Stopped);
        }

        void togglePlayPause() override
        {
            if (_playbackStatus == PlaybackStatus::Playing)
                pause();
            else
                play();
        }

        void play() override
        {
            if (_trackIndex == -1)
                _trackIndex = 0;

            setPlaybackStatus(PlaybackStatus::Playing);
        }

        void pause() override
        {
            setPlaybackStatus(PlaybackStatus::Paused);
        }

        void next() override
        {
            _trackIndex += 1;
        }

        void previous() override
        {
            _trackIndex -= 1;
        }

        void seekToPosition(double position) override
        {
            _position = position;
        }

        void setVolume(double volume) override
        {
            _volume = volume;
        }

        Song* currentSong() override
        {
            return &_fakeSong;
        }

        void toggleFavoriteSong() override
        {
            _fakeSong.setFavorite(!_fakeSong.isFavorite());
        }

        void addToFavorites() override
        {
            _fakeSong.setFavorite(true);
        }

        void removeFromFavorites() override
        {
            _fakeSong.setFavorite(false);
        }

        double position() const override
        {
            return _position;
        }

        PlaybackStatus playbackStatus() const override
        {
            return _playbackStatus;
        }

        bool canSeek() const override
        {
            return true;
        }

        bool canGoNext() const override
        {
            return true;
        }

        bool canGoPrevious() const override
        {
            return true;
        }

        bool canAddToFavorites() const override
        {
            return true;
        }

        double volume() const override
        {
            return _volume;
        }

        QString serviceName() const override
        {
            return "FakePlayer";
        }

        QString serviceLogo() const override
        {
            return "FakePlayer.svg";
        }

        bool isPlaying() const override
        {
            return _playbackStatus == PlaybackStatus::Playing;
        }

        bool isStopped() const override
        {
            return _playbackStatus == PlaybackStatus::Stopped;
        }
    };
}