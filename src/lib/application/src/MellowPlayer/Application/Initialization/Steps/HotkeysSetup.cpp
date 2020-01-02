#include "HotkeysSetup.hpp"
#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

HotkeysSetup::HotkeysSetup(IHotkeys& hotkeys) : _hotkeys(hotkeys)
{

}

void HotkeysSetup::initialize(const MellowPlayer::Domain::Initializable::ResultCallback& resultCallback)
{
    _hotkeys.grab();

    resultCallback(true);
}

void HotkeysSetup::cleanUp()
{
    _hotkeys.unGrab();
}
