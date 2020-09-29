#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

MainWindowViewModel::MainWindowViewModel(ISettingsStore& settingsStore, RunningServicesViewModel& runningServicesViewModel)
        : IMainWindow("MainWindow", this),
          _visible(false),
          _logger(Loggers::logger("MainWindow")),
          _zoom(settingsStore),
          _runningServices(runningServicesViewModel)
{
    connect(&_runningServices, &RunningServicesViewModel::currentIndexChanged, [=](){
        setCurrentPage(_runningServices.currentIndex() != -1 ? runningServicesPage() : selectServicePage());
    });
}

void MainWindowViewModel::show()
{
    LOG_DEBUG(_logger, "show");
    setVisible(true);
}

void MainWindowViewModel::hide()
{
    LOG_DEBUG(_logger, "hide");
    setVisible(false);
}

bool MainWindowViewModel::isVisible() const
{
    return _visible;
}

void MainWindowViewModel::setVisible(bool visible)
{
    if (_visible != visible)
    {
        LOG_DEBUG(_logger, "setVisible " << visible);

        _visible = visible;
        emit visibleChanged();
    }
}

void MainWindowViewModel::requestQuit()
{
    LOG_DEBUG(_logger, "request quit");

    emit quitRequest();
}

void MainWindowViewModel::raise()
{
    LOG_DEBUG(_logger, "raise");

    emit raiseRequested();
}

ZoomViewModel* MainWindowViewModel::zoom()
{
    return &_zoom;
}

QString MainWindowViewModel::currentPage() const
{
    return _currentPage;
}

void MainWindowViewModel::setCurrentPage(const QString& value)
{
    if (_currentPage != value)
    {
        _currentPage = value;
        emit currentPageChanged();
    }
}

QString MainWindowViewModel::selectServicePage() const
{
    return "select";
}

QString MainWindowViewModel::runningServicesPage() const
{
    return "running";
}

bool MainWindowViewModel::isOnRunningServicesPage() const
{
    return currentPage() == runningServicesPage();
}

void MainWindowViewModel::toggleActivePage()
{
    setCurrentPage(currentPage() == selectServicePage() ? runningServicesPage(): selectServicePage());
}

RunningServicesViewModel* MainWindowViewModel::runningServices()
{
    return &_runningServices;
}

void MainWindowViewModel::setFullScreen(bool value)
{
    if (_fullScreen != value)
    {
        _fullScreen = value;
        emit fullScreenChanged();
    }
}

bool MainWindowViewModel::isFullScreen() const
{
    return _fullScreen;
}
