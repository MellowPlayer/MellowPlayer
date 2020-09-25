#include "DependencyPool.hpp"

#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>

#include <MellowPlayer/Presentation/Notifications/PlayerNotifications.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>

#include <Fakes/FakeAlbumArtDownloader.hpp>
#include <Fakes/FakeBinTrayHttpClient.hpp>
#include <Fakes/FakeCommnandLineArguments.hpp>
#include <Fakes/FakeFileDownloader.hpp>
#include <Fakes/FakeHttpClient.hpp>
#include <Fakes/FakeListeningHistoryDatabase.hpp>
#include <Fakes/FakeNotificationPresenter.hpp>
#include <Fakes/FakePlatformUpdater.hpp>
#include <Fakes/FakeSettingsStore.hpp>
#include <Fakes/FakeStreamingServiceLoader.hpp>
#include <Fakes/FakeStreamingServiceWatcher.hpp>
#include <Fakes/FakeThemeLoader.hpp>
#include <Fakes/FakeUserScript.hpp>
#include <Fakes/FakeWorkDispatcher.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;
using namespace MellowPlayer::Presentation::Tests;
using namespace MellowPlayer::Tests;

DependencyPool::DependencyPool()
        : _commandLineArgs(make_unique<FakeCommandLineArguments>()),
          _dataProvider(make_unique<FakeListeningHistoryDatabase>()),
          _contextProperties(std::make_shared<FakeContextProperties>())
{
}

DependencyPool::~DependencyPool() = default;

StreamingServices& DependencyPool::getStreamingServices()
{
    static FakeStreamingServiceLoader streamingServiceLoader;
    static FakeStreamingServiceWatcher streamingServiceWatcher;
    if (_streamingServices == nullptr)
    {
        _streamingServices = make_unique<StreamingServices>(streamingServiceLoader, streamingServiceWatcher);
        _streamingServices->load();
    }
    return *_streamingServices;
}

IStreamingServicesViewModel& DependencyPool::getStreamingServicesViewModel()
{
    if (_streamingServicesViewModel == nullptr)
        _streamingServicesViewModel = make_unique<StreamingServicesViewModel>(getStreamingServices(),
                                                                              getSettings(),
                                                                              getWorkDispatcher(),
                                                                              getStreamingServicesCreator(),
                                                                              getCommandLineArguments(),
                                                                              *_contextProperties,
                                                                              getStreamingServiceViewModelFactory());
    return *_streamingServicesViewModel;
}

Players& DependencyPool::getPlayers()
{
    if (_players == nullptr)
        _players = make_unique<Players>(getStreamingServices());
    return *_players;
}

IStreamingServiceCreator& DependencyPool::getStreamingServicesCreator()
{
    return _streamingServiceCreator;
}

ISettingsStore& DependencyPool::getSettingsStore()
{
    return _settingsStore;
}

Settings& DependencyPool::getSettings()
{
    static SettingsSchemaLoader loader;
    if (_settings == nullptr)
        _settings = make_unique<Settings>(loader, getSettingsStore());
    return *_settings;
}

ICommandLineArguments& DependencyPool::getCommandLineArguments()
{
    return *_commandLineArgs;
}

IWorkDispatcher& DependencyPool::getWorkDispatcher()
{
    static FakeWorkDispatcher instance;
    return instance;
}

ListeningHistoryViewModel& DependencyPool::getListeningHistoryViewModel()
{
    if (_listeningHistoryViewModel == nullptr)
        _listeningHistoryViewModel = make_unique<ListeningHistoryViewModel>(getListeningHistory(), *_contextProperties);
    return *_listeningHistoryViewModel;
}

ListeningHistory& DependencyPool::getListeningHistory()
{
    if (_listeningHistory == nullptr)
        _listeningHistory = make_unique<ListeningHistory>(*_dataProvider, getCurrentPlayer(), getSettings());
    return *_listeningHistory;
}

IPlayer& DependencyPool::getCurrentPlayer()
{
    if (_currentPlayer == nullptr)
        _currentPlayer = make_unique<CurrentPlayer>(getPlayers(), getStreamingServices());
    return *_currentPlayer;
}

ThemeViewModel& DependencyPool::getThemeViewModel()
{
    static auto themeLoader = FakeThemeLoader();
    if (_themeViewModel == nullptr)
        _themeViewModel = make_unique<ThemeViewModel>(getStreamingServices(), getSettings(), themeLoader, *_contextProperties);
    return *_themeViewModel;
}

UpdaterViewModel& DependencyPool::getUpdaterViewModel()
{
    if (_updaterViewModel == nullptr)
        _updaterViewModel = make_unique<UpdaterViewModel>(getUpdater(), *_contextProperties);
    return *_updaterViewModel;
}

Updater& DependencyPool::getUpdater()
{
    static LatestBinTrayRelease latestBinTrayRelease(std::make_unique<FakeBinTrayHttpClient>());
    if (_updater == nullptr)
        _updater = make_unique<Updater>(latestBinTrayRelease, getSettings(), getPlatformUpdater());
    return *_updater;
}

IPlayerNotifications& DependencyPool::playerNotifications()
{
    if (_notifications == nullptr)
        _notifications =
                make_unique<PlayerNotifications>(getCurrentPlayer(), getLocalAlbumArt(), getNotificationPresenter(), getStreamingServices(), getSettings());
    return *_notifications;
}

INotificationPresenter& DependencyPool::getNotificationPresenter()
{
    return _notificationPresenter;
}

LocalAlbumArt& DependencyPool::getLocalAlbumArt()
{
    static FakeAlbumArtDownloader downloader;

    if (_localAlbumArt == nullptr)
        _localAlbumArt = make_unique<LocalAlbumArt>(getCurrentPlayer(), downloader);
    return *_localAlbumArt;
}

FakeNotificationPresenter& DependencyPool::getFakeNotificationPresenter()
{
    return _notificationPresenter;
}

AbstractPlatformUpdater& DependencyPool::getPlatformUpdater()
{
    static FakeFileDownloader fakeFileDownloader;
    if (_platformUpdater == nullptr)
        _platformUpdater = make_unique<FakePlatformUpdater>(fakeFileDownloader);
    return *_platformUpdater;
}

IUserScriptFactory& DependencyPool::getUserScriptFactory()
{
    return _userScriptsFactory;
}

IContextProperties& DependencyPool::getContextProperties()
{
    return *_contextProperties;
}

INetworkProxies& DependencyPool::getNetworkProxies()
{
    return _networkProxies;
}

IStreamingServiceViewModelFactory& DependencyPool::getStreamingServiceViewModelFactory()
{
    if (_streamingServiceViewModelFactory == nullptr)
    {
        _streamingServiceViewModelFactory = std::make_unique<StreamingServiceViewModelFactory>(
                getSettingsStore(), getUserScriptFactory(), getPlayers(), getNetworkProxies(), getThemeViewModel(), _httpClientFactory);
    }
    return *_streamingServiceViewModelFactory;
}
