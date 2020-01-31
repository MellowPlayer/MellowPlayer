#pragma once

#include <MellowPlayer/Infrastructure/System/IProcess.hpp>
#include <QStringList>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IShellScript;

    class IShellScriptFactory
    {
    public:
        virtual ~IShellScriptFactory() = default;

        virtual std::shared_ptr<IShellScript> create() = 0;
    };
}

