#pragma once

#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>

using namespace MellowPlayer::Domain;

#define LOCAL_URL "/path/to/art/songId"

class FakeAlbumArtDownloader : public IAlbumArtDownloader
{
public:
    void block()
    {
        _blocked = true;
        if (!_localArtUrl.isEmpty())
            emit downloadFinished(_localArtUrl);
    }

    void unblock()
    {
        _blocked = false;
    }

    bool download(const QString& artUrl, const QString& songId) override
    {
        _artUrl = artUrl;
        _localArtUrl = LOCAL_URL + songId;

        if (!_blocked)
            emit downloadFinished(_localArtUrl);

        return !_blocked;
    }

    QFileInfo localArtUrl(const QString&) override
    {
        return QFileInfo(_localArtUrl);
    }

    QString artUrl()
    {
        return _artUrl;
    }

    QString localArtUrl()
    {
        return _localArtUrl;
    }

private:
    QString _artUrl;
    QString _localArtUrl;
    bool _blocked = true;
};
