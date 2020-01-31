#pragma once

#include <MellowPlayer/Infrastructure/System/IShellScriptFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class ITextFileFactory;
    class IProcessFactory;

    class ShellScriptFactory : public IShellScriptFactory
    {
    public:
        ShellScriptFactory(ITextFileFactory& textFileFactory, IProcessFactory& processFactory);
        std::shared_ptr<IShellScript> create() override;

    private:
        ITextFileFactory& _textFileFactory;
        IProcessFactory& _processFactory;
    };
}
