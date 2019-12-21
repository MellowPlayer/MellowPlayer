#pragma once

#include <MellowPlayer/Infrastructure/CommandLineArguments/CommandLineArguments.hpp>
#include <QString>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class IApplication;
    class ApplicationNetworkProxy;
}

namespace MellowPlayer::Application
{
    class InitializationSequence;

    class Program
    {
    public:
        Program(InitializationSequence& initializationSequence, Infrastructure::IApplication& application);
        int execute();

        static int main(int argc, char** argv);

    private:
        void initialize() const;
        void cleanUp() const;

        Domain::ILogger& _logger;
        InitializationSequence& _initializationSequence;
        Infrastructure::IApplication& _application;
    };
}
