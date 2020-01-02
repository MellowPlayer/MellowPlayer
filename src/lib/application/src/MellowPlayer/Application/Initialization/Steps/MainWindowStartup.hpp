#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;
}

namespace MellowPlayer::Presentation
{
    class IMainWindow;
}

namespace MellowPlayer::Application
{
    class MainWindowStartup : public Domain::Initializable
    {
    Q_OBJECT
    public:
        explicit MainWindowStartup(Presentation::IMainWindow& mainWindow, Infrastructure::ICommandLineArguments& commandLineArguments);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::IMainWindow& _mainWindow;
        Infrastructure::ICommandLineArguments& _commandLineArguments;
    };
}
