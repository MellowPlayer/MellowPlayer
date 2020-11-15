#include <MellowPlayer/Infrastructure/PlatformFilters/LinuxFilter.hpp>

using namespace MellowPlayer::Infrastructure;

bool LinuxFilter::match() const
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    return true;
#else
    return false;
#endif
}
