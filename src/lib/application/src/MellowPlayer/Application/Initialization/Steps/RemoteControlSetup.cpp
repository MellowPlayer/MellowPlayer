#include "RemoteControlSetup.hpp"
#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Application;

RemoteControlSetup::RemoteControlSetup(IRemoteControl& remoteControl) : _remoteControl(remoteControl)
{

}

void RemoteControlSetup::initialize(const ResultCallback& resultCallback)
{
    if (_remoteControl.isEnabled())
        _remoteControl.activate();
    else
        _remoteControl.deactivate();

    resultCallback(true);
}
