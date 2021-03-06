#pragma once

#include "IPlayer.hpp"
#include "Song.hpp"
#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class IPlayerBase;
    class Players;
    class StreamingServices;
    class StreamingService;

    class CurrentPlayer : public IPlayer
    {
        Q_OBJECT
        Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
    public:
        CurrentPlayer(Players& players, StreamingServices& streamingServices);
        virtual ~CurrentPlayer();

        Q_INVOKABLE bool isActive();
        Q_INVOKABLE void togglePlayPause() override;
        Q_INVOKABLE void play() override;
        Q_INVOKABLE void pause() override;
        Q_INVOKABLE void next() override;
        Q_INVOKABLE void previous() override;
        Q_INVOKABLE void seekToPosition(double position) override;
        Q_INVOKABLE void setVolume(double volume) override;
        Q_INVOKABLE void toggleFavoriteSong() override;
        Q_INVOKABLE void addToFavorites() override;
        Q_INVOKABLE void removeFromFavorites() override;

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

    signals:
        void activeChanged();

    private slots:
        void onCurrentServiceChanged(Domain::StreamingService* streamingService);

    private:
        Players& _players;
        StreamingServices& _streamingServices;
        Domain::Song _nullSong;

        std::shared_ptr<IPlayerBase> _currentPlayer;
    };
}
