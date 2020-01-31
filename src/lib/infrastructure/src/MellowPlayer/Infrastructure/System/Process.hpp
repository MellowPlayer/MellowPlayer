#pragma once

#include <MellowPlayer/Infrastructure/System/IProcess.hpp>
#include <QtCore/QProcess>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class Process : public QObject, public IProcess
    {
        Q_OBJECT
    public:
        Process(const QString& name);

        void setProgram(const QString& program) override;
        void setArguments(const QStringList& arguments) override;
        void setWorkingDirectory(const QString& workingDirectory) override;
        void setBufferizeStandardOutput(bool value) override;
        void setBufferizeErrorOutput(bool value) override;
        void setLogOutput(bool value) override;
        void execute(const ExecuteCallback& callback) override;

    private slots:
        void onReadyReadStandardOutput();
        void onReadyReadErrorOutput();
        void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

    private:
        void readOutput(const QProcess::ProcessChannel channel);

        bool _bufferizeStandardOutput = false;
        bool _bufferizeErrorOutput = false;
        bool _logOutput = true;
        QStringList _standardOutput;
        QStringList _errorOutput;
        QProcess _qProcess;
        Domain::ILogger& _logger;
        ExecuteCallback _callback;
    };
}