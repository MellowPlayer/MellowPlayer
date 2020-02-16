#include "MellowPlayer/Presentation/IconProvider.hpp"
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>

#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>

#include <QDesktopServices>
#include <QtCore/QDebug>
#include <QtGui/QFontDatabase>
#include <QProcess>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

ApplicationViewModel::ApplicationViewModel(IApplication& application,
                                           IQtApplication& qtApplication,
                                           IMainWindow& mainWindow,
                                           IContextProperties& contextProperties)
        : ContextProperty("_app", this, contextProperties),
          _application(application),
          _qtApplication(qtApplication),
          _mainWindow(mainWindow),
          _restartRequested(false)
{
    _qtApplication.setWindowIcon(IconProvider::windowIcon());

    connect(&_application, &IApplication::commitDataRequest, &mainWindow, &IMainWindow::forceQuitRequest);
    connect(&_application, &IApplication::restoreWindowRequest, &mainWindow, &IMainWindow::raise);
}

void ApplicationViewModel::quit()
{
    _application.quit();
}

void ApplicationViewModel::restart()
{
    _application.restart();
}

void ApplicationViewModel::showLogs()
{
    auto logDirectory = FileHelper::logDirectory();
    auto logFile = QUrl::fromLocalFile(logDirectory + "All.log");
#ifdef Q_OS_UNIX
    QProcess::startDetached("xdg-open", {logFile.toString()});
#else
    QDesktopServices::openUrl(logFile);
#endif

}

QString ApplicationViewModel::buildInfo() const
{
    return BuildConfig::buildInfo();
}
