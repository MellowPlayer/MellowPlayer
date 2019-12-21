#include <MellowPlayer/Infrastructure/PlatformFilters/AppImageFilter.hpp>

using namespace MellowPlayer::Infrastructure;

bool AppImageFilter::match() const
{
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    return _isAppImage;
#else
    return false;
#endif
}
