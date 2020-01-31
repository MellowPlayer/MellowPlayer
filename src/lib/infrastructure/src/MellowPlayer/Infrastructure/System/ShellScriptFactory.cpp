#include "ShellScriptFactory.hpp"
#include "ShellScript.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

ShellScriptFactory::ShellScriptFactory(ITextFileFactory& textFileFactory, IProcessFactory& processFactory)
        : _textFileFactory(textFileFactory), _processFactory(processFactory)
{
}

shared_ptr<IShellScript> ShellScriptFactory::create()
{
    return make_shared<ShellScript>(_textFileFactory, _processFactory);
}
