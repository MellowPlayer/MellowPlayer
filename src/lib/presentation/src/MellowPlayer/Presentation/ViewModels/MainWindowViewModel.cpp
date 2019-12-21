#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

MainWindowViewModel::MainWindowViewModel(std::shared_ptr<IContextProperties> contextProperties, IQmlApplicationEngine& qmlApplicationEngine)
        : ContextProperty("_window", this, contextProperties), _qmlApplicationEngine(qmlApplicationEngine), _visible(false)
{
}

void MainWindowViewModel::show()
{
    setVisible(true);
}

void MainWindowViewModel::load()
{
    _qmlApplicationEngine.addImportPath("qrc:/MellowPlayer/imports");
    _qmlApplicationEngine.load(QUrl("qrc:/MellowPlayer/main.qml"));
}

void MainWindowViewModel::hide()
{
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
        _visible = visible;
        emit visibleChanged();
    }
}

void MainWindowViewModel::requestQuit()
{
    emit quitRequest();
}

void MainWindowViewModel::raise()
{
    emit raiseRequested();
}
