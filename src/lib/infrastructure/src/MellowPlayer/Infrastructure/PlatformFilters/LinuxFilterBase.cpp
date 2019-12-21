#include <MellowPlayer/Infrastructure/PlatformFilters/LinuxFilterBase.hpp>

using namespace MellowPlayer::Infrastructure;

LinuxFilterBase::LinuxFilterBase() : _isAppImage(false)
{
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty())
        _isAppImage = true;
}
