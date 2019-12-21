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
          _mainWindow(mainWindow),
          _updater(updater),
          _listeningHistory(listeningHistory),
          _streamingServices(streamingServices),
          _cache(contextProperties),
          _cookies(contextProperties),
          _clipboard(contextProperties),
          _devToolsWindow(contextProperties),
          _zoomViewModel(zoomViewModel),
          _commandLineArguments(commandLineOptions)
{
}

void QmlSetup::initialize(const ResultCallback& resultCallback)
{
    _application.initialize();
    _cache.clear();
    _streamingServices.initialize();
    _listeningHistory.initialize();
    _mainWindow.load();
    if (!_commandLineArguments.startMinimized())
        _mainWindow.show();
    else
        _mainWindow.hide();
    _updater.check();

    resultCallback(true);
}

void QmlSetup::cleanUp()
{
    _mainWindow.hide();
    _cache.clear();
}

QString QmlSetup::toString() const
{
    return "QmlSetup";
}
