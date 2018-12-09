#include <QtCore/QThread>
#include <MellowPlayer/Presentation/ViewModels/ViewModels.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

ViewModels::ViewModels(ApplicationViewModel&,
                       IMainWindow& mainWindow,
                       SettingsViewModel&,
                       ThemeViewModel&,
                       UpdaterViewModel& updater,
                       ListeningHistoryViewModel& listeningHistory,
                       StreamingServicesViewModel& streamingServices,
                       IContextProperties& contextProperties,
                       ICommandLineArguments& commandLineOptions)
        : mainWindow_(mainWindow),
          updater_(updater),
          listeningHistory_(listeningHistory),
          streamingServices_(streamingServices),
          cache_(contextProperties),
          cookies_(contextProperties),
          clipboard_(contextProperties),
          devToolsWindow_(contextProperties),
          commandLineArguments_(commandLineOptions)
{

}

void ViewModels::initialize()
{
    cache_.clear();
    streamingServices_.initialize();
    listeningHistory_.initialize();
    mainWindow_.load();
    if (!commandLineArguments_.startMinimized())
        mainWindow_.show();
    else
        mainWindow_.hide();
    updater_.check();
}

void ViewModels::cleanup()
{
    cache_.clear();
}

