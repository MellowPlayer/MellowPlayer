#pragma once

#include <memory>
#include <MellowPlayer/Macros.hpp>
#include "IPlayer.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)
PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePlugin)
PREDECLARE_MELLOWPLAYER_CLASS(Entities, StreamingServicePluginScript)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ILogger;

class Player: public IPlayer
{
    Q_OBJECT
public:
    Player(Entities::StreamingServicePlugin& plugin);
    ~Player();

    // IPlayer
    Q_INVOKABLE void togglePlayPause() override;
    Q_INVOKABLE void play() override;
    Q_INVOKABLE void pause() override;
    Q_INVOKABLE void next() override;
    Q_INVOKABLE void previous() override;
    Q_INVOKABLE void seekToPosition(double value) override;
    Q_INVOKABLE void setVolume(double volume) override;
    Q_INVOKABLE void toggleFavoriteSong() override;
    Q_INVOKABLE void addToFavorites() override;
    Q_INVOKABLE void removeFromFavorites() override;

    Entities::Song* getCurrentSong() override;
    double getPosition() const override;
    PlaybackStatus getPlaybackStatus() const override;
    bool getCanSeek() const override;
    bool getCanGoNext() const override;
    bool getCanGoPrevious() const override;
    bool getCanAddToFavorites() const override;
    double getVolume() const override;
    QString getServiceName() const override;
    bool isPlaying() const override;
    bool isStopped() const override;

    // invoked by WebView (QML)
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void setUpdateResults(const QVariant& results);

    // invoked by PlayerProxy
    void suspend();
    void resume();

    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;

    void setPlaybackStatus(PlaybackStatus value);

signals:
    void runJavascriptRequested(const QString& script);
    void updateRequested(const QString& script);

private:
    void setCurrentSong(std::unique_ptr<Entities::Song>& song);
    void setPosition(double value);
    void setCanSeek(bool value);
    void setCanGoNext(bool value);
    void setCanGoPrevious(bool value);
    void setCanAddToFavorites(bool value);
    void setCurrentVolume(double value);

    ILogger& logger;
    double position = false;
    PlaybackStatus playbackStatus = PlaybackStatus::Stopped;
    bool canSeek = false;
    bool canGoNext = false;
    bool canGoPrevious = false;
    bool canAddToFavorites = false;
    double volume = 1;
    std::unique_ptr<Entities::Song> currentSong;
    Entities::StreamingServicePlugin& plugin;
    Entities::StreamingServicePluginScript& pluginScript;
    PlaybackStatus suspendedState = PlaybackStatus::Stopped;
};

END_MELLOWPLAYER_NAMESPACE