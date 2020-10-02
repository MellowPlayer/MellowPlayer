#pragma once

#include <Fakes/FakeHttpClientFactory.hpp>
#include <Fakes/FakeNetworkProxies.hpp>
#include <Fakes/FakeNotificationPresenter.hpp>
#include <Fakes/FakeQmlSingletons.hpp>
#include <Fakes/FakeSettingsStore.hpp>
#include <Fakes/FakeStreamingServiceCreator.hpp>
#include <Fakes/FakeUserScriptFactory.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModelFactory.hpp>
#include <memory>

class FakeListeningHistoryDatabase;

namespace MellowPlayer::Domain
{
    class CurrentPlayer;
    class IPlayer;
    class IWorkDispatcher;
    class ListeningHistory;
    class Players;
    class Settings;
    class StreamingServices;
}

namespace MellowPlayer::Infrastructure
{
    class LocalAlbumArt;
    class ICommandLineArguments;
    class Updater;
    class AbstractPlatformUpdater;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel;
    class IStreamingServicesViewModel;
    class ThemeViewModel;
    class UpdaterViewModel;
    class IPlayerNotifications;
    class INotificationPresenter;
}

namespace MellowPlayer::Tests
{
    class DependencyPool
    {
    public:
        DependencyPool();
        ~DependencyPool();

        // Domain Layer
        Domain::StreamingServices& getStreamingServices();
        Domain::IPlayer& getCurrentPlayer();
        Domain::Players& getPlayers();
        Domain::IStreamingServiceCreator& getStreamingServicesCreator();
        Domain::ISettingsStore& getSettingsStore();
        Domain::Settings& getSettings();
        Domain::IWorkDispatcher& getWorkDispatcher();
        Domain::ListeningHistory& getListeningHistory();
        Domain::IUserScriptFactory& getUserScriptFactory();

        // Infrastructure layer
        Infrastructure::Updater& getUpdater();
        Infrastructure::AbstractPlatformUpdater& getPlatformUpdater();
        Infrastructure::LocalAlbumArt& getLocalAlbumArt();
        Infrastructure::ICommandLineArguments& getCommandLineArguments();
        Infrastructure::INetworkProxies& getNetworkProxies();

        // Presentation Layer
        Presentation::IPlayerNotifications& playerNotifications();
        Presentation::IStreamingServiceViewModelFactory& getStreamingServiceViewModelFactory();
        Presentation::IStreamingServicesViewModel& getStreamingServicesViewModel();
        Presentation::ListeningHistoryViewModel& getListeningHistoryViewModel();
        Presentation::ThemeViewModel& getThemeViewModel();
        Presentation::UpdaterViewModel& getUpdaterViewModel();
        Presentation::INotificationPresenter& getNotificationPresenter();
        Presentation::FakeNotificationPresenter& getFakeNotificationPresenter();

    private:
        std::unique_ptr<Infrastructure::ICommandLineArguments> _commandLineArgs;
        Domain::Tests::FakeSettingsStore _settingsStore;
        Domain::FakeStreamingServiceCreator _streamingServiceCreator;
        Presentation::FakeNotificationPresenter _notificationPresenter;
        Domain::Tests::FakeUserScriptFactory _userScriptsFactory;

        // app
        std::unique_ptr<Domain::CurrentPlayer> _currentPlayer;
        std::unique_ptr<Domain::ListeningHistory> _listeningHistory;
        std::unique_ptr<Domain::Players> _players;
        std::unique_ptr<Domain::Settings> _settings;
        std::unique_ptr<Domain::StreamingServices> _streamingServices;

        // infra
        std::unique_ptr<Infrastructure::LocalAlbumArt> _localAlbumArt;
        std::unique_ptr<Infrastructure::Updater> _updater;
        std::unique_ptr<Infrastructure::AbstractPlatformUpdater> _platformUpdater;

        // presentation
        std::unique_ptr<Presentation::ListeningHistoryViewModel> _listeningHistoryViewModel;
        FakeHttpClientFactory _httpClientFactory;
        std::unique_ptr<Presentation::StreamingServiceViewModelFactory> _streamingServiceViewModelFactory;
        std::unique_ptr<Presentation::IStreamingServicesViewModel> _streamingServicesViewModel;
        std::unique_ptr<Presentation::ThemeViewModel> _themeViewModel;
        std::unique_ptr<Presentation::UpdaterViewModel> _updaterViewModel;
        std::unique_ptr<Presentation::IPlayerNotifications> _notifications;

        std::unique_ptr<FakeListeningHistoryDatabase> _dataProvider;

        Infrastructure::Tests::FakeNetworkProxies _networkProxies;
    };
}
