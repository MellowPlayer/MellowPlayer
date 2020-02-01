#pragma once

#include <QStringList>
#include <functional>

namespace MellowPlayer::Infrastructure
{
    class IProcess
    {
    public:
        using ExecuteCallback = std::function<void(int exitCode, const QString& standardOutput, const QString& errorOutput)>;

        virtual ~IProcess() = default;

        virtual void setProgram(const QString& program) = 0;
        virtual void setArguments(const QStringList& arguments) = 0;
        virtual void setWorkingDirectory(const QString& value) = 0;
        virtual void setBufferizeStandardOutput(bool value) = 0;
        virtual void setBufferizeErrorOutput(bool value) = 0;
        virtual void setLogOutput(bool value) = 0;

        virtual void execute(const ExecuteCallback& callback) = 0;
        virtual void stop() = 0;
    };
}