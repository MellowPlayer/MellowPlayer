#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>
#include <QVariant>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

Player::Player(StreamingService& streamingService)
        : _logger(Loggers::logger("Player-" + streamingService.name().toStdString())), _currentSong(nullptr), _streamingService(streamingService)
{
}

Player::~Player() = default;

void Player::togglePlayPause()
{
    LOG_TRACE(_logger, "togglePlayePause");
    if (_playbackStatus == PlaybackStatus::Playing)
        pause();
    else
        play();
}

void Player::seekToPosition(double value)
{
    emit seekToPositionRequest(value);
    setPosition(value);
}

void Player::setVolume(double value)
{
    if (value != _volume)
    {
        _volume = value;
        emit changeVolumeRequest(value);
        emit volumeChanged();
    }
}

void Player::toggleFavoriteSong()
{
    LOG_TRACE(_logger, "toggleFavoriteSong()");
    if (_currentSong == nullptr)
        return;

    if (_currentSong->isFavorite())
        removeFromFavorites();
    else
        addToFavorites();
}

Song* Player::currentSong()
{
    return _currentSong.get();
}

double Player::position() const
{
    return _position;
}

PlaybackStatus Player::playbackStatus() const
{
    return _playbackStatus;
}

bool Player::canSeek() const
{
    return _canSeek;
}

bool Player::canGoNext() const
{
    return _canGoNext;
}

bool Player::canGoPrevious() const
{
    return _canGoPrevious;
}

bool Player::canAddToFavorites() const
{
    return _canAddToFavorites;
}

double Player::volume() const
{
    return _volume;
}

QString Player::serviceName() const
{
    return _streamingService.name();
}

void Player::setUpdateResults(const QVariant& results)
{
    QVariantMap resultsMap = results.toMap();

    QString uniqueId = resultsMap.value("songId").toString().replace("-", "");
    QString title = resultsMap.value("songTitle").toString().replace("\n", "").trimmed();
    QString artist = resultsMap.value("artistName").toString().replace("\n", "").trimmed();
    QString album = resultsMap.value("albumTitle").toString().replace("\n", "").trimmed();
    QString artUrl = resultsMap.value("artUrl").toString();
    double duration = resultsMap.value("duration").toDouble();
    bool isFavorite = resultsMap.value("isFavorite").toBool();
    auto song = make_unique<Song>(uniqueId, title, artist, album, artUrl, duration, isFavorite);

    PlaybackStatus status = static_cast<PlaybackStatus>(resultsMap.value("playbackStatus").toInt());
    if (status == PlaybackStatus::Paused && !song->isValid())
        status = PlaybackStatus::Stopped;
    setPlaybackStatus(status);
    setCurrentSong(song);
    setPosition(resultsMap.value("position").toDouble());
    setCanSeek(resultsMap.value("canSeek").toBool());
    setCanGoNext(resultsMap.value("canGoNext").toBool());
    setCanGoPrevious(resultsMap.value("canGoPrevious").toBool());
    setCanAddToFavorites(resultsMap.value("canAddToFavorites").toBool());
    setCurrentVolume(resultsMap.value("volume").toDouble());
}

void Player::suspend()
{
    LOG_DEBUG(_logger, "suspend()");
    _suspendedState = _playbackStatus;
    if (_playbackStatus == PlaybackStatus::Playing)
    {
        pause();
        _playbackStatus = PlaybackStatus::Paused;
    }
}

void Player::resume()
{
    LOG_DEBUG(_logger, "resume()");
    if (_suspendedState == PlaybackStatus::Playing)
    {
        play();
    }
}

void Player::setCurrentSong(unique_ptr<Song>& song)
{
    if (_currentSong != nullptr && *_currentSong == *song)
    {
        _currentSong->setDuration(song->duration());
        _currentSong->setFavorite(song->isFavorite());
        _currentSong->setArtUrl(song->artUrl());
        return;
    }

    _currentSong = std::move(song);
    LOG_DEBUG(_logger, "song changed: " + (_currentSong->isValid() ? _currentSong->toString() : "NullSong"));
    LOG_TRACE(_logger, "song id:" + _currentSong->uniqueId());
    LOG_TRACE(_logger, "artUrl:" + _currentSong->artUrl());
    emit currentSongChanged(_currentSong.get());
}

void Player::setPosition(double value)
{
    if (value == _position)
        return;

    _position = value;
    emit positionChanged();
}

void Player::setPlaybackStatus(PlaybackStatus value)
{
    if (value == _playbackStatus)
        return;

    _playbackStatus = value;
    LOG_DEBUG(_logger, "playback status changed: " << static_cast<int>(value));
    emit playbackStatusChanged();
    emit isPlayingChanged();
    emit isStoppedChanged();
}

void Player::setCanSeek(bool value)
{
    if (value == _canSeek)
        return;

    _canSeek = value;
    emit canSeekChanged();
}

void Player::setCanGoNext(bool value)
{
    if (value == _canGoNext)
        return;

    _canGoNext = value;
    emit canGoNextChanged();
}

void Player::setCanGoPrevious(bool value)
{
    if (value == _canGoPrevious)
        return;

    _canGoPrevious = value;
    emit canGoPreviousChanged();
}

void Player::setCanAddToFavorites(bool value)
{
    if (value == _canAddToFavorites)
        return;

    _canAddToFavorites = value;
    emit canAddToFavoritesChanged();
}

void Player::setCurrentVolume(double value)
{
    if (value == _volume)
        return;

    _volume = value;
    emit volumeChanged();
}

bool Player::operator==(const Player& other) const
{
    return _streamingService == other._streamingService;
}

bool Player::operator!=(const Player& other) const
{
    return !operator==(other);
}

bool Player::isPlaying() const
{
    return _playbackStatus == PlaybackStatus::Playing;
}

bool Player::isStopped() const
{
    return _playbackStatus == PlaybackStatus::Stopped;
}

QString Player::serviceLogo() const
{
    return _streamingService.logo();
}
