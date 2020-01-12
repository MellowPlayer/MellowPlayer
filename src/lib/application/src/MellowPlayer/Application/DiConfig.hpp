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
#include <MellowPlayer/Infrastructure/RemoteControl/MellowPlayerConnect.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <MellowPlayer/Infrastructure/System/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/System/TextFileFactory.hpp>
#include <MellowPlayer/Infrastructure/System/Timer.hpp>
#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/ILatestRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <MellowPlayer/Presentation/Hotkeys/Hotkeys.hpp>
#include <MellowPlayer/Presentation/Notifications/PlayerNotifications.hpp>
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
        di::bind<IApplication>().to<Application>().in(di::singleton).in(scope),
        di::bind<IQtApplication>().to<QtApplication>().in(scope),
        di::bind<IQmlApplicationEngine>().to<QmlApplicationEngine>().in(scope),
        di::bind<IContextProperties>().to<ContextProperties>().in(di::singleton).in(scope),
        di::bind<IPlayer>().to<CurrentPlayer>().in(di::singleton).in(scope),
        di::bind<ILocalSocketFactory>().to<LocalSocketFactory>().in(scope),
        di::bind<ILocalServerFactory>().to<LocalServerFactory>().in(scope),
        di::bind<IStreamingServiceLoader>().to<StreamingServiceLoader>().in(di::singleton).in(scope),
        di::bind<IStreamingServiceWatcher>().to<StreamingServiceWatcher>().in(di::singleton).in(scope),
        di::bind<ILoggerFactory>().to<SpdLoggerFactory>().in(di::singleton).in(scope),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(di::singleton).in(scope),
        di::bind<ILocalAlbumArt>().to<LocalAlbumArt>().in(di::singleton).in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(di::singleton).in(scope),
        di::bind<IListeningHistoryDatabase>().to<SqlLiteListeningHistoryDatabase>().in(di::singleton).in(scope),
        di::bind<ISettingsStore>().to<QSettingsStore>().in(di::singleton).in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(di::singleton).in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(di::singleton).in(scope),
        di::bind<IStreamingServiceCreator>().to<StreamingServiceCreator>().in(di::singleton).in(scope),
        di::bind<IThemeLoader>().to<ThemeLoader>().in(di::singleton).in(scope),
        di::bind<ILatestRelease>().to<LatestBinTrayRelease>().in(di::singleton).in(scope),
        di::bind<IHttpClient>().to<HttpClient>().in(di::singleton).in(scope),
        di::bind<IFileDownloader>().to<FileDownloader>().in(di::singleton).in(scope),
        di::bind<IUserScriptFactory>().to<UserScriptFactory>().in(di::singleton).in(scope),
        di::bind<IMainWindow>().to<MainWindowViewModel>().in(di::singleton).in(scope),
        di::bind<INetworkProxies>().to<NetworkProxies>().in(di::singleton).in(scope),
        di::bind<ITimer>().to<Timer>().in(di::unique),
        di::bind<IListeningHistory>().to<DelayedListeningHistory>().in(di::singleton).in(scope),
        di::bind<IPlayerNotifications>().to<PlayerNotifications>().in(di::singleton).in(scope),
        di::bind<IHotkeys>().to<Hotkeys>().in(di::singleton).in(scope),
        di::bind<IApplicationStatusFile>().to<ApplicationStatusFile>().in(di::singleton).in(scope),
        di::bind<ITextFileFactory>().to<TextFileFactory>().in(di::singleton).in(scope),
        di::bind<IRemoteControl>().to<RemoteControl>().in(di::singleton).in(scope),
        di::bind<IRemoteControlApplication>().to<MellowPlayerConnect>().in(di::singleton).in(scope),

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
        di::bind<AbstractPlatformUpdater>().to<LinuxUpdater>().in(di::singleton).in(scope),
        di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(di::singleton).in(scope),
#elif defined(Q_OS_WIN)
        di::bind<AbstractPlatformUpdater>().to<WindowsUpdater>().in(di::singleton).in(scope),
        di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>()).in(di::singleton).in(scope),
#elif defined(Q_OS_OSX)
        di::bind<AbstractPlatformUpdater>().to<OSXUpdater>().in(di::singleton).in(scope),
        di::make_injector(di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>()).in(di::singleton).in(scope),
#endif

        di::bind<Initializable* []>().to<
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
                FontsSetup,
                TranslationsSetup,
                QmlTypesSetup,
                QmlEngineStartup,
                MainWindowStartup,
                CacheCleanup,
                ApplicationUpdatesCheckup,
                RemoteControlCheckup,
                RemoteControlStartup
        >()
    );
};

// clang-format on
