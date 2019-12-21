#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/ViewModels/QmlSetup.hpp>
#include <QDesktopServices>
#include <QtCore/QDirIterator>
#include <QtCore/QThread>
#include <QtGui/QFontDatabase>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

QmlSetup::QmlSetup(ApplicationViewModel& application,
                   IMainWindow& mainWindow,
                   SettingsViewModel&,
                   ThemeViewModel&,
                   UpdaterViewModel& updater,
                   ListeningHistoryViewModel& listeningHistory,
                   StreamingServicesViewModel& streamingServices,
                   std::shared_ptr<IContextProperties> contextProperties,
                   ZoomViewModel& zoomViewModel,
                   ICommandLineArguments& commandLineOptions)
        : _application(application),
          mainWindow_(mainWindow),
          updater_(updater),
          listeningHistory_(listeningHistory),
          streamingServices_(streamingServices),
          cache_(contextProperties),
          cookies_(contextProperties),
          clipboard_(contextProperties),
          devToolsWindow_(contextProperties),
          zoomViewModel_(zoomViewModel),
          commandLineArguments_(commandLineOptions)
{
}

void QmlSetup::initialize(const ResultCallback& resultCallback)
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

    resultCallback(true);
}

void QmlSetup::cleanUp()
{
    mainWindow_.hide();
    cache_.clear();
}

QString QmlSetup::toString() const
{
    return "QmlSetup";
}
