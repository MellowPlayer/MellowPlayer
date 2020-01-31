#pragma once

#include <MellowPlayer/Infrastructure/System/IProcess.hpp>
#include <QStringList>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IShellScript
    {
    public:
        virtual ~IShellScript() = default;

        virtual void setInterpreter(const QString& interpreter) = 0;
        // FOR SCRIPT THAT ALREADY EXISTS ON FILESYSTEM OR IN A QRC FILE
        virtual void setScript(const QString& path) = 0;
        // WRITE SCRIPT CONTENT IN SPECIFIED PATH
        virtual void setScript(const QString& content, const QString& path) = 0;
        virtual void setScriptArguments(const QStringList& arguments) = 0;

        virtual void execute(const IProcess::ExecuteCallback& executeCallback) = 0;
    };
}

