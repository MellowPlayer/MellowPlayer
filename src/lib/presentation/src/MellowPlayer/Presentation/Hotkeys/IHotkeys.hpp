#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>

namespace MellowPlayer::Presentation
{
    class IHotkeys : public Domain::IInitializable
    {
    public:
        virtual ~IHotkeys() = default;

        virtual void togglePlayPause() = 0;
        virtual void next() = 0;
        virtual void previous() = 0;
        virtual void toggleFavoriteSong() = 0;
        virtual void restoreWindow() = 0;
    };
}
