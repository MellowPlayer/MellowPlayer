#pragma once

#ifdef USE_LIBNOTIFY
#    include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyPresenter.hpp>
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
#    include <MellowPlayer/Application/Initialization/Steps/QmlTypesSetup.hpp>
#    include <MellowPlayer/Infrastructure/Updater/Linux/LinuxUpdater.hpp>
#    include <MellowPlayer/Presentation/Mpris/Linux/MprisStartup.hpp>
#elif defined(Q_OS_WIN)
#    include <MellowPlayer/Infrastructure/Updater/Windows/WindowsUpdater.hpp>
#elif defined(Q_OS_OSX)
#    include <MellowPlayer/Infrastructure/Updater/OSX/OSXUpdater.hpp>
#endif

#include <MellowPlayer/Application/Initialization/InitializationSequence.hpp>
#include <MellowPlayer/Application/Initialization/Steps/AdBlockSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/ApplicationUpdatesCheckup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/CacheCleanup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/FontsSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/HotkeysSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/ListeningHistorySetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/MainWindowStartup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/NotificationsSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/QmlEngineStartup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/QmlTypesSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/RemoteControlCheckup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/RemoteControlSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/RemoteControlStartup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/SingleInstanceCheckup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/StreamingServicesSetup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/SystemTrayIconStartup.hpp>
#include <MellowPlayer/Application/Initialization/Steps/TranslationsSetup.hpp>
#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/ListeningHistory/IListeningHistoryDatabase.hpp>
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/RemoteControl/RemoteControl.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/AdBlock/FileBlockListLoader.hpp>
#include <MellowPlayer/Infrastructure/AdBlock/HttpBlockListLoader.hpp>
#include <MellowPlayer/Infrastructure/AdBlock/IFileBlockListLoader.hpp>
#include <MellowPlayer/Infrastructure/AdBlock/IHttpBlockListLoader.hpp>
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
#include <MellowPlayer/Infrastructure/Network/HttpClientFactory.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/RemoteControl/MellowPlayerConnect.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <MellowPlayer/Infrastructure/System/ProcessFactory.hpp>
#include <MellowPlayer/Infrastructure/System/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/System/ShellScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/System/TextFileFactory.hpp>
#include <MellowPlayer/Infrastructure/System/Timer.hpp>
#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/ILatestRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <MellowPlayer/Presentation/AdBlock/AdBlockRequestInterceptor.hpp>
#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>
#include <MellowPlayer/Presentation/Notifications/PlayerNotifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/SystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlSingletons.hpp>
#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingletons.hpp>
#include <MellowPlayer/Presentation/ViewModels/ActiveThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModelFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
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
        di::bind<IApplication>().to<Application>().in(di::singleton),
        di::bind<IQtApplication>().to<QtApplication>().in(scope),
        di::bind<IQmlApplicationEngine>().to<QmlApplicationEngine>().in(scope),
        di::bind<IQmlSingletons>().to<QmlSingletons>().in(di::singleton),
        di::bind<IPlayer>().to<CurrentPlayer>().in(di::singleton),
        di::bind<ILocalSocketFactory>().to<LocalSocketFactory>().in(scope),
        di::bind<ILocalServerFactory>().to<LocalServerFactory>().in(scope),
        di::bind<IStreamingServiceLoader>().to<StreamingServiceLoader>().in(di::singleton),
        di::bind<IStreamingServiceWatcher>().to<StreamingServiceWatcher>().in(di::singleton),
        di::bind<ILoggerFactory>().to<SpdLoggerFactory>().in(di::singleton),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(di::singleton),
        di::bind<ILocalAlbumArt>().to<LocalAlbumArt>().in(di::singleton),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(di::singleton),
        di::bind<IListeningHistoryDatabase>().to<SqlLiteListeningHistoryDatabase>().in(di::singleton),
        di::bind<ISettingsStore>().to<QSettingsStore>().in(di::singleton),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(di::singleton),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(di::singleton),
        di::bind<IStreamingServiceCreator>().to<StreamingServiceCreator>().in(di::singleton),
        di::bind<IThemeLoader>().to<ThemeLoader>().in(di::singleton),
        di::bind<ILatestRelease>().to<LatestBinTrayRelease>().in(di::singleton),
        di::bind<IHttpClient>().to<HttpClient>().in(di::unique),
        di::bind<IHttpClientFactory>().to<HttpClientFactory>().in(di::singleton),
        di::bind<IFileDownloader>().to<FileDownloader>().in(di::singleton),
        di::bind<IUserScriptFactory>().to<UserScriptFactory>().in(di::singleton),
        di::bind<IMainWindow>().to<MainWindowViewModel>().in(di::singleton),
        di::bind<INetworkProxies>().to<NetworkProxies>().in(di::singleton),
        di::bind<ITimer>().to<Timer>().in(di::unique),
        di::bind<IListeningHistory>().to<DelayedListeningHistory>().in(di::singleton),
        di::bind<IPlayerNotifications>().to<PlayerNotifications>().in(di::singleton),
        di::bind<IHotkeys>().to<Hotkeys>().in(di::singleton),
        di::bind<IApplicationStatusFile>().to<ApplicationStatusFile>().in(di::singleton),
        di::bind<ITextFileFactory>().to<TextFileFactory>().in(di::singleton),
        di::bind<IProcessFactory>().to<ProcessFactory>().in(di::singleton),
        di::bind<IShellScriptFactory>().to<ShellScriptFactory>().in(di::singleton),
        di::bind<IRemoteControl>().to<RemoteControl>().in(di::singleton),
        di::bind<IRemoteControlApplication>().to<MellowPlayerConnect>().in(di::singleton),
        di::bind<IAdBlockRequestInterceptor>().to<AdBlockRequestInterceptor>().in(di::unique),
        di::bind<IFileBlockListLoader>().to<FileBlockListLoader>().in(di::singleton),
        di::bind<IHttpBlockListLoader>().to<HttpBlockListLoader>(),
        di::bind<IStreamingServiceViewModelFactory>().to<StreamingServiceViewModelFactory>(),
        di::bind<IStreamingServicesViewModel>().to<StreamingServicesViewModel>(),

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
        di::bind<AbstractPlatformUpdater>().to<LinuxUpdater>().in(di::singleton),
        di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(di::singleton),
#elif defined(Q_OS_WIN)
        di::bind<AbstractPlatformUpdater>().to<WindowsUpdater>().in(di::singleton),
        di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>()).in(di::singleton),
#elif defined(Q_OS_OSX)
        di::bind<AbstractPlatformUpdater>().to<OSXUpdater>().in(di::singleton),
        di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>()).in(di::singleton),
#endif
        di::bind<IQmlSingleton* []>().to<
                ActiveThemeViewModel,
                ApplicationViewModel,
                ClipBoardViewModel,
                DevToolsWindowViewModel,
                MainWindowViewModel,
                RemoteControlViewModel,
                UpdaterViewModel,
                ListeningHistoryViewModel,
                StreamingServicesViewModel
        >(),
        di::bind<Initializable* []>().to<
                AdBlockSetup,
                SingleInstanceCheckup,
                RemoteControlSetup,
                StreamingServicesSetup,
                ListeningHistorySetup,
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
                MprisStartup,
#endif
                HotkeysSetup,
                SystemTrayIconStartup,
                NotificationsSetup,
                RemoteControlCheckup,
                RemoteControlStartup,
                FontsSetup,
                TranslationsSetup,
                QmlTypesSetup,
                QmlEngineStartup,
                MainWindowStartup,
                CacheCleanup,
                ApplicationUpdatesCheckup
        >()
    );
};

// clang-format on
