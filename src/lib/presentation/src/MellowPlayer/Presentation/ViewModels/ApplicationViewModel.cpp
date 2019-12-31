#include "MellowPlayer/Presentation/IconProvider.hpp"
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <QDesktopServices>
#include <QtCore/QDebug>
#include <QtCore/QDirIterator>
#include <QtGui/QFontDatabase>
#include <QtWebEngineWidgets/QWebEngineProfile>

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
    QDesktopServices::openUrl(logDirectory + "All.log");
}

void ApplicationViewModel::setupFont()
{
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-ThinItalic.ttf");
    _qtApplication.setFont(QFont("Roboto"));
}

void ApplicationViewModel::registerMetaTypes()
{
    qRegisterMetaType<Song*>("Domain::Song*");
    qRegisterMetaType<Song*>("Song*");
    qRegisterMetaType<StreamingService*>("Domain::StreamingService*");
    qRegisterMetaType<StreamingService*>("StreamingService*");
    qRegisterMetaType<ListeningHistoryEntry>("Domain::ListeningHistoryEntry");
    qRegisterMetaType<ListeningHistoryEntry>("ListeningHistoryEntry");
    qRegisterMetaType<Player*>("Domain::Player*");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<SettingViewModel*>("Presentation::SettingViewModel*");
    qRegisterMetaType<SettingViewModel*>("SettingViewModel*");
}

void ApplicationViewModel::setupTranslations()
{
    if (!_translator.load(QLocale(), "MellowPlayer", "_", ":/MellowPlayer/Translations"))
    {
        qWarning() << "failed to load translation: " << QLocale::system().name();
    }
    else
        qInfo() << "translation successfully loaded: " << QLocale::system().name();

    qInfo() << "available translations: ";
    QDirIterator it(":/MellowPlayer/Translations", QStringList() << "*.qm", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qInfo() << "  - " << it.next();

    _qtApplication.installTranslator(&_translator);
}

QString ApplicationViewModel::buildInfo() const
{
    return BuildConfig::buildInfo();
}

void ApplicationViewModel::initialize()
{
    setupFont();
    registerMetaTypes();
    setupTranslations();
}
