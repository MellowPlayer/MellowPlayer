#pragma once

#ifdef USE_LIBNOTIFY
#    include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyPresenter.hpp>
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#    include <MellowPlayer/Infrastructure/Updater/Linux/LinuxUpdater.hpp>
#    include <MellowPlayer/Presentation/Mpris/Linux/MprisService.hpp>
#    include <MellowPlayer/Presentation/ViewModels/QmlSetup.hpp>
#elif defined(Q_OS_WIN)
#    include <MellowPlayer/Infrastructure/Updater/Windows/WindowsUpdater.hpp>
#elif defined(Q_OS_OSX)
#    include <MellowPlayer/Infrastructure/Updater/OSX/OSXUpdater.hpp>
#endif

#include <MellowPlayer/Application/Initialization/InitializationSequence.hpp>
#include <MellowPlayer/Application/Initialization/SingleInstanceCheck.hpp>
#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/Application/Application.hpp>
#include <MellowPlayer/Infrastructure/Application/ApplicationStatusFile.hpp>
#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/CommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/DelayedListeningHistory.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDatabase.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Infrastructure/Network/ApplicationNetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <MellowPlayer/Infrastructure/Network/HttpClient.hpp>
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <MellowPlayer/Infrastructure/Timer.hpp>
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/ILatestRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>
#include <MellowPlayer/Presentation/Hotkeys/IHotkeys.hpp>
#include <MellowPlayer/Presentation/Mpris/IMprisService.hpp>
#include <MellowPlayer/Presentation/Mpris/NullMprisService.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Notifications/Notifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/QmlSetup.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <boost-di-extensions/Factory.hpp>
#include <boost/di.hpp>
#include <boost/di/extension/scopes/scoped.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Application;

namespace di = boost::di;

// clang-format off
auto defaultInjector = [](di::extension::detail::scoped& scope, QApplication& qApplication, ICommandLineArguments& commandLineArguments) {
    return di::make_injector(
        di::bind<QApplication>().to(qApplication),
        di::bind<ICommandLineArguments>().to(commandLineArguments),
        di::bind<IApplication>().to<Application>().in(scope),
        di::bind<IQtApplication>().to<QtApplication>().in(scope),
        di::bind<IQmlApplicationEngine>().to<QmlApplicationEngine>().in(scope),
        di::bind<IContextProperties>().to<ContextProperties>().in(scope),
        di::bind<IPlayer>().to<CurrentPlayer>().in(scope),
        di::bind<IFactory<ILocalSocket>>().to(Factory<LocalSocket> { }),
        di::bind<IFactory<ILocalServer, QString>>().to(Factory<LocalServer> { }),
        di::bind<IStreamingServiceLoader>().to<StreamingServiceLoader>().in(scope),
        di::bind<IStreamingServiceWatcher>().to<StreamingServiceWatcher>().in(scope),
        di::bind<ILoggerFactory>().to<SpdLoggerFactory>().in(scope),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<ILocalAlbumArt>().to<LocalAlbumArt>().in(scope),
        di::bind<IHotkeys>().to<Hotkeys>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<IListeningHistoryDatabase>().to<SqlLiteListeningHistoryDatabase>().in(scope),
        di::bind<ISettingsStore>().to<QSettingsStore>().in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope),
        di::bind<IStreamingServiceCreator>().to<StreamingServiceCreator>().in(scope),
        di::bind<IThemeLoader>().to<ThemeLoader>().in(scope),
        di::bind<ILatestRelease>().to<LatestBinTrayRelease>().in(scope),
        di::bind<IHttpClient>().to<HttpClient>().in(scope),
        di::bind<IFileDownloader>().to<FileDownloader>().in(scope),
        di::bind<IUserScriptFactory>().to<UserScriptFactory>().in(scope),
        di::bind<IMainWindow>().to<MainWindowViewModel>().in(scope),
        di::bind<INotifications>().to<Notifications>().in(scope),
        di::bind<INetworkProxies>().to<NetworkProxies>().in(scope),
        di::bind<ITimer>().to<Timer>().in(di::unique),
        di::bind<IListeningHistory>().to<DelayedListeningHistory>().in(scope),

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
        di::bind<AbstractPlatformUpdater>().to<LinuxUpdater>().in(scope),
        di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(scope),
#elif defined(Q_OS_WIN)
        di::bind<IMprisService>().to<NullMprisService>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<WindowsUpdater>().in(scope),
        di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>()).in(scope),
#elif defined(Q_OS_OSX)
        di::bind<IMprisService>().to<NullMprisService>().in(scope),
        di::bind<AbstractPlatformUpdater>().to<OSXUpdater>().in(scope),
        di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>()).in(scope),
#endif

        di::bind<IInitializable* []>().to<
                SingleInstanceCheck,
                ApplicationStatusFile,
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
                MprisService,
#endif
                IHotkeys,
                IContextProperties,
                QmlSetup,
                Notifications,
                SystemTrayIcon
        >()
    );
};

// clang-format on
