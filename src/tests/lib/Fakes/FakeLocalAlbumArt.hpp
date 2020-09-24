#pragma once

#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>

namespace MellowPlayer::Domain
{
    class FakeLocalAlbumArt : public ILocalAlbumArt
    {
    public:
        QString url() const override
        {
            return "/path/to/album/art.jpg";
        }

        void setReady(bool value)
        {
            _ready = value;
        }

        bool isReady(const Song&) override
        {
            return _ready;
        }

    private:
        bool _ready = true;
    };
}