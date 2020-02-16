#include "Process.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

Process::Process(const QString& name) : _logger(Loggers::logger(QString("Process[%1]").arg(name).toStdString()))
{
    connect(&_qProcess, &QProcess::readyReadStandardOutput, this, &Process::onReadyReadStandardOutput);
    connect(&_qProcess, &QProcess::readyReadStandardError, this, &Process::onReadyReadErrorOutput);
    connect(&_qProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Process::onFinished);
}

Process::~Process()
{
    stop();
}

void Process::setProgram(const QString& program)
{
    _qProcess.setProgram(program);
}

void Process::setArguments(const QStringList& arguments)
{
    _qProcess.setArguments(arguments);
}

void Process::setWorkingDirectory(const QString& workingDirectory)
{
    _qProcess.setWorkingDirectory(workingDirectory);
}

void Process::setBufferizeStandardOutput(bool value)
{
    _bufferizeStandardOutput = value;
}

void Process::setBufferizeErrorOutput(bool value)
{
    _bufferizeErrorOutput = value;
}

void Process::setLogOutput(bool value)
{
    _logOutput = value;
}

void Process::execute(const ExecuteCallback& callback)
{
    _callback = callback;
    LOG_DEBUG(_logger, "Starting process " << _qProcess.program() << " " << _qProcess.arguments().join(" ") << " @ " << _qProcess.workingDirectory());

    _qProcess.start();
}

void Process::onReadyReadStandardOutput()
{
    readOutput(QProcess::StandardOutput);
}

void Process::onReadyReadErrorOutput()
{
    readOutput(QProcess::StandardError);
}

void Process::readOutput(const QProcess::ProcessChannel channel)
{
    _qProcess.setReadChannel(channel);
    while(_qProcess.canReadLine())
    {
        auto line = _qProcess.readLine().replace("\n", "");

        if (_logOutput)
            LOG_DEBUG(_logger, (channel == QProcess::StandardOutput ? "stdout: " : "stderr: ") << line.toStdString());

        if (channel == QProcess::StandardOutput && _bufferizeStandardOutput)
            _standardOutput.append(line);

        if (channel == QProcess::StandardError && _bufferizeErrorOutput)
            _errorOutput.append(line);
    }
}

void Process::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit)
    {
        LOG_WARN(_logger, "Process crashed, exit code = " << exitCode);
    }
    else
    {
        LOG_DEBUG(_logger, "process finished normally, exit code = " << exitCode);
    }

    _callback(exitCode, _standardOutput.join("\n"), _errorOutput.join("\n"));
}
void Process::stop()
{
    if (_qProcess.isOpen())
    {
        _qProcess.terminate();
#ifdef Q_OS_WIN
        _qProcess.kill();
#endif
        _qProcess.waitForFinished();
    }
}
