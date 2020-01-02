#include "ApplicationUpdatesCheckup.hpp"
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

ApplicationUpdatesCheckup::ApplicationUpdatesCheckup(UpdaterViewModel& updater) : _updater(updater)
{

}

void ApplicationUpdatesCheckup::initialize(const MellowPlayer::Domain::Initializable::ResultCallback& resultCallback)
{
    _updater.check();
    resultCallback(true);
}
