#include "CacheCleanup.hpp"
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

CacheCleanup::CacheCleanup(ApplicationViewModel& applicationViewModel) : _applicationViewModel(applicationViewModel)
{

}
void CacheCleanup::cleanUp()
{
    _applicationViewModel.clearCache();
}
