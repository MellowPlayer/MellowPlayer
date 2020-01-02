#pragma once

#include <fakeit/fakeit.hpp>
#include <memory>

#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>
#include <UnitTests/Infrastructure/Network/FakeNetworkProxies.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>

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
    class StreamingServicesViewModel;
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

        // Mock Objects
        fakeit::Mock<Presentation::INotificationPresenter>& getNotificationPresenterMock();

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
        Presentation::StreamingServicesViewModel& getStreamingServicesViewModel();
        Presentation::ListeningHistoryViewModel& getListeningHistoryViewModel();
        Presentation::ThemeViewModel& getThemeViewModel();
        Presentation::UpdaterViewModel& getUpdaterViewModel();
        Presentation::INotificationPresenter& getNotificationPresenter();
        Presentation::IContextProperties& getContextProperties();

    private:
        // mocks
        std::unique_ptr<Infrastructure::ICommandLineArguments> _commandLineArgs;
        Domain::Tests::FakeSettingsStore _settingsStore;
        fakeit::Mock<Domain::IStreamingServiceCreator> _streamingServiceCreator;
        fakeit::Mock<Presentation::INotificationPresenter> _notificationPresenter;
        fakeit::Mock<Domain::IUserScriptFactory> _userScriptsFactoryMock;

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
        std::unique_ptr<Presentation::StreamingServicesViewModel> _streamingServicesViewModel;
        std::unique_ptr<Presentation::ThemeViewModel> _themeViewModel;
        std::unique_ptr<Presentation::UpdaterViewModel> _updaterViewModel;
        std::unique_ptr<Presentation::IPlayerNotifications> _notifications;

        std::unique_ptr<FakeListeningHistoryDatabase> _dataProvider;

        std::shared_ptr<Presentation::Tests::FakeContextProperties> _contextProperties;
        Infrastructure::Tests::FakeNetworkProxies _networkProxies;
    };
}
