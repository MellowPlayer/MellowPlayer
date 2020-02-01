#include "ShellScript.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/System/IProcess.hpp>
#include <MellowPlayer/Infrastructure/System/IProcessFactory.hpp>
#include <MellowPlayer/Infrastructure/System/ITextFile.hpp>
#include <MellowPlayer/Infrastructure/System/ITextFileFactory.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMap>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

ShellScript::ShellScript(ITextFileFactory& textFileFactory, IProcessFactory& processFactory)
        : _textFileFactory(textFileFactory), _processFactory(processFactory), _logger(Loggers::logger("ShellScript"))
{
}

void ShellScript::setInterpreter(const QString& interpreter)
{
    _interpreter = interpreter;
}

void ShellScript::setScript(const QString& path)
{
    if (path.startsWith(":"))
    {
        auto textFile = _textFileFactory.create(path);
        auto tempPath = QDir::tempPath() + QDir::separator() + QFileInfo(path).fileName();
        auto content = textFile->read();
        setScript(content, tempPath);
    }
    else
    {
        _path = path;
        _interpreter = detectInterpreter(path);
    }
}

void ShellScript::setScript(const QString& content, const QString& path)
{
    auto textFile = _textFileFactory.create(path);
    textFile->write(content);
    setScript(path);
}

void ShellScript::setScriptArguments(const QStringList& arguments)
{
    _arguments = arguments;
}

void ShellScript::execute(const IProcess::ExecuteCallback& executeCallback)
{
    _process = _processFactory.create(QFileInfo(_path).baseName());
    _process->setProgram(_interpreter);
    _process->setArguments(QStringList{_path} + _arguments);
    _process->setBufferizeErrorOutput(true);
    _process->execute(executeCallback);
}

QString ShellScript::detectInterpreter(const QString& path)
{
    QMap<QString, QString> interpreters{{"sh", "/usr/bin/bash"}, {"bat", "cmd.exe"}, {"ps1", "powershell.exe"}};
    auto scriptExtension = QFileInfo(path).suffix();

    if (interpreters.contains(scriptExtension))
        return interpreters[scriptExtension];
    return "";
}
