#pragma once

#include <MellowPlayer/Infrastructure/System/IShellScript.hpp>

namespace MellowPlayer::Infrastructure
{
    class ITextFileFactory;
    class IProcessFactory;

    class ShellScript : public IShellScript
    {
    public:
        ShellScript(ITextFileFactory& textFileFactory, IProcessFactory& processFactory);

        void setInterpreter(const QString& interpreter) override;
        void setScript(const QString& path) override;
        void setScript(const QString& content, const QString& path) override;
        void setScriptArguments(const QStringList& arguments) override;

        void execute(const IProcess::ExecuteCallback& executeCallback) override;

    private:
        static QString detectInterpreter(const QString& path);

        ITextFileFactory& _textFileFactory;
        IProcessFactory& _processFactory;

        QString _interpreter;
        QString _path;
        QStringList _arguments;

        std::shared_ptr<IProcess> _process;
    };
}
