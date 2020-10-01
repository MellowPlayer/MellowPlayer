#pragma once

#include "IPlayer.hpp"
#include <memory>

class QTimer;

namespace MellowPlayer::Domain
{
    class ILogger;
    class Song;
    class StreamingService;
    class StreamingServiceScript;

    // TODO Replace by PlayerViewModel
    class IPlayerBase : public IPlayer
    {
        Q_OBJECT
    public:
        // invoked by WebView (QML)
        virtual Q_INVOKABLE void setUpdateResults(const QVariant& results) = 0;

        virtual void suspend() = 0;
        virtual void resume() = 0;
        virtual void setPlaybackStatus(PlaybackStatus value) = 0;

    signals:
        void play() override;
        void pause() override;
        void next() override;
        void previous() override;
        void addToFavorites() override;
        void removeFromFavorites() override;
        void seekToPositionRequest(double newPosition);
        void changeVolumeRequest(double newVolume);
    };

    class Player : public IPlayerBase
    {
        Q_OBJECT
    public:
        explicit Player(Domain::StreamingService& streamingService);
        ~Player() override;

        Q_INVOKABLE void seekToPosition(double value) override;
        Q_INVOKABLE void setVolume(double volume) override;
        Q_INVOKABLE void togglePlayPause() override;
        Q_INVOKABLE void toggleFavoriteSong() override;

        Domain::Song* currentSong() override;
        double position() const override;
        PlaybackStatus playbackStatus() const override;
        bool canSeek() const override;
        bool canGoNext() const override;
        bool canGoPrevious() const override;
        bool canAddToFavorites() const override;
        double volume() const override;
        QString serviceName() const override;
        QString serviceLogo() const override;
        bool isPlaying() const override;
        bool isStopped() const override;


        Q_INVOKABLE void setUpdateResults(const QVariant& results) override;

        // invoked by CurrentPlayer
        void suspend();
        void resume();

        bool operator==(const Player& other) const;
        bool operator!=(const Player& other) const;

        void setPlaybackStatus(PlaybackStatus value) override;

    private:
        void setCurrentSong(std::unique_ptr<Domain::Song>& song);
        void setPosition(double value);
        void setCanSeek(bool value);
        void setCanGoNext(bool value);
        void setCanGoPrevious(bool value);
        void setCanAddToFavorites(bool value);
        void setCurrentVolume(double value);

        ILogger& _logger;
        double _position = false;
        PlaybackStatus _playbackStatus = PlaybackStatus::Stopped;
        bool _canSeek = false;
        bool _canGoNext = false;
        bool _canGoPrevious = false;
        bool _canAddToFavorites = false;
        double _volume = 1;
        std::unique_ptr<Domain::Song> _currentSong;
        Domain::StreamingService& _streamingService;
        PlaybackStatus _suspendedState = PlaybackStatus::Stopped;
    };
}
