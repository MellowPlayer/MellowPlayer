#include <MellowPlayer/Infrastructure/UserScripts/UserScript.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

IUserScript* UserScriptFactory::create()
{
    return new UserScript;
}
