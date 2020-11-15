#pragma once

#include <MellowPlayer/Infrastructure/PlatformFilters/IPlatformFilter.hpp>

namespace MellowPlayer::Infrastructure
{
    class LinuxFilter : public IPlatformFilter
    {
    public:
        bool match() const override;
    };
}
