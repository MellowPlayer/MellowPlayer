#pragma once

#include <QString>

namespace MellowPlayer::Infrastructure
{
    class IPlatform;

    class IPlatformFilter
    {
    public:
        virtual ~IPlatformFilter() = default;

        virtual bool match() const = 0;
    };
}
