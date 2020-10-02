#include "MellowPlayer/Presentation/IconProvider.hpp"
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>

#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>

#include <QDesktopServices>
#include <QDebug>
#include <QFontDatabase>
#include <QProcess>
#include <QDir>
#include <QStandardPaths>
#include <QWebEngineProfile>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

ApplicationViewModel::ApplicationViewModel(IApplication& application,
                                           IQtApplication& qtApplication,
                                           MainWindowViewModel& mainWindow)
        : QmlSingleton("ApplicationViewModel", this),
          _application(application),
          _qtApplication(qtApplication),
          _mainWindow(mainWindow),
          _restartRequested(false)
{
    _qtApplication.setWindowIcon(IconProvider::windowIcon());

    connect(&_application, &IApplication::commitDataRequest, &mainWindow, &MainWindowViewModel::forceQuitRequest);
    connect(&_application, &IApplication::restoreWindowRequest, &mainWindow, &MainWindowViewModel::raise);
}

void ApplicationViewModel::quit()
{
    _mainWindow.runningServices()->clear();
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

void ApplicationViewModel::clearCache()
{
    // clear http cache
    auto& profile = *QWebEngineProfile::defaultProfile();
    profile.clearHttpCache();

    // clear mellowplayer cache (covers,...)
    for (auto dir : QStandardPaths::standardLocations(QStandardPaths::CacheLocation))
    {
        QDir cacheDir(dir);
        qDebug() << "removing cache directory: " << dir;
        cacheDir.removeRecursively();
    }
}

void ApplicationViewModel::clearCookies()
{
    auto& profile = *QWebEngineProfile::defaultProfile();
    QDir storageDir(profile.persistentStoragePath());
    qDebug() << "removing persistent storage directory: " << storageDir;
    storageDir.removeRecursively();
}
