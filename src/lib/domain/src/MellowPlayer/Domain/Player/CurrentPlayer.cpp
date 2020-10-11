#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

CurrentPlayer::CurrentPlayer(Players& players, StreamingServices& streamingServices)
        : _players(players), _streamingServices(streamingServices), _currentPlayer(nullptr)
{
    connect(&streamingServices, &StreamingServices::currentChanged, this, &CurrentPlayer::onCurrentServiceChanged);

    if (streamingServices.current() != nullptr)
        onCurrentServiceChanged(streamingServices.current());
}

void CurrentPlayer::togglePlayPause()
{
    if (_currentPlayer)
        _currentPlayer->togglePlayPause();
}

void CurrentPlayer::play()
{
    if (_currentPlayer)
        _currentPlayer->play();
}

void CurrentPlayer::pause()
{
    if (_currentPlayer)
        _currentPlayer->pause();
}

void CurrentPlayer::next()
{
    if (_currentPlayer)
        _currentPlayer->next();
}

void CurrentPlayer::previous()
{
    if (_currentPlayer)
        _currentPlayer->previous();
}

void CurrentPlayer::seekToPosition(double position)
{
    if (_currentPlayer)
        _currentPlayer->seekToPosition(position);
}

void CurrentPlayer::setVolume(double volume)
{
    if (_currentPlayer)
        _currentPlayer->setVolume(volume);
}

void CurrentPlayer::toggleFavoriteSong()
{
    if (_currentPlayer)
        _currentPlayer->toggleFavoriteSong();
}

void CurrentPlayer::addToFavorites()
{
    if (_currentPlayer)
        _currentPlayer->addToFavorites();
}

void CurrentPlayer::removeFromFavorites()
{
    if (_currentPlayer)
        _currentPlayer->removeFromFavorites();
}

Song* CurrentPlayer::currentSong()
{
    if (_currentPlayer != nullptr && _currentPlayer->currentSong() != nullptr)
        return _currentPlayer->currentSong();
    return &_nullSong;
}

double CurrentPlayer::position() const
{
    if (_currentPlayer)
        return _currentPlayer->position();
    return 0;
}

PlaybackStatus CurrentPlayer::playbackStatus() const
{
    if (_currentPlayer)
        return _currentPlayer->playbackStatus();
    return PlaybackStatus::Stopped;
}

bool CurrentPlayer::canSeek() const
{
    if (_currentPlayer)
        return _currentPlayer->canSeek();
    return false;
}

bool CurrentPlayer::canGoNext() const
{
    if (_currentPlayer)
        return _currentPlayer->canGoNext();
    return false;
}

bool CurrentPlayer::canGoPrevious() const
{
    if (_currentPlayer)
        return _currentPlayer->canGoPrevious();
    return false;
}

bool CurrentPlayer::canAddToFavorites() const
{
    if (_currentPlayer)
        return _currentPlayer->canAddToFavorites();
    return false;
}

double CurrentPlayer::volume() const
{
    if (_currentPlayer)
        return _currentPlayer->volume();
    return 0;
}

void CurrentPlayer::onCurrentServiceChanged(StreamingService* streamingService)
{
    auto player = streamingService == nullptr ? nullptr : _players.get(streamingService->name());
    if (player != _currentPlayer)
    {
        if (_currentPlayer != nullptr)
        {
            disconnect(_currentPlayer.get(), &Player::currentSongChanged, this, &CurrentPlayer::activeChanged);
            disconnect(_currentPlayer.get(), &Player::currentSongChanged, this, &CurrentPlayer::currentSongChanged);
            disconnect(_currentPlayer.get(), &Player::positionChanged, this, &CurrentPlayer::positionChanged);
            disconnect(_currentPlayer.get(), &Player::playbackStatusChanged, this, &CurrentPlayer::playbackStatusChanged);
            disconnect(_currentPlayer.get(), &Player::canSeekChanged, this, &CurrentPlayer::canSeekChanged);
            disconnect(_currentPlayer.get(), &Player::canGoNextChanged, this, &CurrentPlayer::canGoNextChanged);
            disconnect(_currentPlayer.get(), &Player::canGoPreviousChanged, this, &CurrentPlayer::canGoPreviousChanged);
            disconnect(_currentPlayer.get(), &Player::canAddToFavoritesChanged, this, &CurrentPlayer::canAddToFavoritesChanged);
            disconnect(_currentPlayer.get(), &Player::volumeChanged, this, &CurrentPlayer::volumeChanged);
            disconnect(_currentPlayer.get(), &Player::isPlayingChanged, this, &CurrentPlayer::isPlayingChanged);
            disconnect(_currentPlayer.get(), &Player::isStoppedChanged, this, &CurrentPlayer::isStoppedChanged);
            _currentPlayer->suspend();
        }

        _currentPlayer = player;

        if (_currentPlayer)
        {
            connect(_currentPlayer.get(), &Player::currentSongChanged, this, &CurrentPlayer::activeChanged);
            connect(_currentPlayer.get(), &Player::currentSongChanged, this, &CurrentPlayer::currentSongChanged);
            connect(_currentPlayer.get(), &Player::positionChanged, this, &CurrentPlayer::positionChanged);
            connect(_currentPlayer.get(), &Player::playbackStatusChanged, this, &CurrentPlayer::playbackStatusChanged);
            connect(_currentPlayer.get(), &Player::canSeekChanged, this, &CurrentPlayer::canSeekChanged);
            connect(_currentPlayer.get(), &Player::canGoNextChanged, this, &CurrentPlayer::canGoNextChanged);
            connect(_currentPlayer.get(), &Player::canGoPreviousChanged, this, &CurrentPlayer::canGoPreviousChanged);
            connect(_currentPlayer.get(), &Player::canAddToFavoritesChanged, this, &CurrentPlayer::canAddToFavoritesChanged);
            connect(_currentPlayer.get(), &Player::volumeChanged, this, &CurrentPlayer::volumeChanged);
            connect(_currentPlayer.get(), &Player::isPlayingChanged, this, &CurrentPlayer::isPlayingChanged);
            connect(_currentPlayer.get(), &Player::isStoppedChanged, this, &CurrentPlayer::isStoppedChanged);
            _currentPlayer->resume();
            emit currentSongChanged(_currentPlayer->currentSong());
        }
        else
        {
            emit currentSongChanged(nullptr);
        }
        emit activeChanged();
        emit positionChanged();
        emit playbackStatusChanged();
        emit canSeekChanged();
        emit canGoNextChanged();
        emit canGoPreviousChanged();
        emit canAddToFavoritesChanged();
        emit volumeChanged();
        emit isPlayingChanged();
        emit isStoppedChanged();
    }
}

QString CurrentPlayer::serviceName() const
{
    if (_currentPlayer)
        return _currentPlayer->serviceName();
    return "";
}

bool CurrentPlayer::isPlaying() const
{
    if (_currentPlayer)
        return _currentPlayer->isPlaying();
    return false;
}

bool CurrentPlayer::isStopped() const
{
    if (_currentPlayer)
        return _currentPlayer->isStopped();
    return true;
}

QString CurrentPlayer::serviceLogo() const
{
    if (_currentPlayer)
        return _currentPlayer->serviceLogo();
    return "";
}
CurrentPlayer::~CurrentPlayer()
{

}

bool CurrentPlayer::isActive()
{
    return currentSong() != nullptr && currentSong()->isValid();
}
