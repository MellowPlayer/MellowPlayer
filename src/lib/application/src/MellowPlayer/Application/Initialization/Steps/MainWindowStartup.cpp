#include "MainWindowStartup.hpp"
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

MainWindowStartup::MainWindowStartup(IMainWindow& mainWindow, ICommandLineArguments& commandLineArguments)
        : _mainWindow(mainWindow), _commandLineArguments(commandLineArguments)
{

}

void MainWindowStartup::initialize(const ResultCallback& resultCallback)
{
    if (_commandLineArguments.startMinimized())
        _mainWindow.hide();
    else
        _mainWindow.show();

    resultCallback(true);
}
