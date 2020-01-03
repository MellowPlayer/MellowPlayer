#include "RemoteControlSetup.hpp"
#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Application;

RemoteControlSetup::RemoteControlSetup(IRemoteControl& remoteControl) : _remoteControl(remoteControl)
{

}

void RemoteControlSetup::initialize(const ResultCallback& resultCallback)
{
    _remoteControl.activate();

    resultCallback(true);
}

bool RemoteControlSetup::isEnabled() const
{
    return _remoteControl.isEnabled();
}
