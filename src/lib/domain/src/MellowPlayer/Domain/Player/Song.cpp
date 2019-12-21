#include <MellowPlayer/Domain/Player/Song.hpp>
#include <cmath>

using namespace std;
using namespace MellowPlayer::Domain;

Song::Song() : _duration(0), _isFavorite(false)
{
}

Song::Song(const QString& uniqueId, const QString& title, const QString& artist, const QString& album, const QString& artUrl, double duration, bool isFavorite)
        : _uniqueId(uniqueId), _title(title), _artist(artist), _album(album), _artUrl(artUrl), _duration(duration), _isFavorite(isFavorite)
{
}

QString Song::uniqueId() const
{
    return _uniqueId;
}

QString Song::title() const
{
    return _title;
}

QString Song::artist() const
{
    return _artist;
}

QString Song::album() const
{
    return _album;
}

QString Song::artUrl() const
{
    return _artUrl;
}

double Song::duration() const
{
    return _duration;
}

bool Song::isFavorite() const
{
    return _isFavorite;
}

void Song::setDuration(double value)
{
    if (abs(_duration - value) < 2)
        return;

    _duration = value;
    emit durationChanged();
}

void Song::setFavorite(bool value)
{
    if (value == _isFavorite)
        return;

    _isFavorite = value;
    emit isFavoriteChanged();
}

void Song::setArtUrl(const QString& artUrl)
{
    if (artUrl != _artUrl)
    {
        _artUrl = artUrl;
        emit artUrlChanged();
    }
}
