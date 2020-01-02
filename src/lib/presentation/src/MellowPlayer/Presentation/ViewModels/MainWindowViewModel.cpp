#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

MainWindowViewModel::MainWindowViewModel(IContextProperties& contextProperties)
        : ContextProperty("_window", this, contextProperties), _visible(false), _logger(Loggers::logger("MainWindow"))
{
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
