#include "CacheCleanup.hpp"
#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

CacheCleanup::CacheCleanup(CacheViewModel& cache) : _cache(cache)
{

}
void CacheCleanup::cleanUp()
{
    _cache.clear();
}
