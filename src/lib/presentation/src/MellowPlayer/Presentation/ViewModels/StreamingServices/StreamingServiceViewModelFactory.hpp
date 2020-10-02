#pragma once

namespace MellowPlayer::Domain
{
    class ISettingsStore;
    class IUserScriptFactory;
    class StreamingService;
    class Players;
}

namespace MellowPlayer::Infrastructure
{
    class IHttpClientFactory;
    class INetworkProxies;
}

namespace MellowPlayer::Presentation
{
    class IStreamingServiceViewModel;
    class ActiveThemeViewModel;

    class IStreamingServiceViewModelFactory
    {
    public:
        virtual ~IStreamingServiceViewModelFactory() = default;

        virtual IStreamingServiceViewModel* create(Domain::StreamingService& streamingService, QObject* parent) = 0;
    };

    class StreamingServiceViewModelFactory : public IStreamingServiceViewModelFactory
    {
    public:
        StreamingServiceViewModelFactory(Domain::ISettingsStore& settingsStore,
                                         Domain::IUserScriptFactory& userScriptFactory,
                                         Domain::Players& players,
                                         Infrastructure::INetworkProxies& networkProxies,
                                         ActiveThemeViewModel& themeViewModel,
                                         Infrastructure::IHttpClientFactory& httpClientFactory);

        IStreamingServiceViewModel* create(Domain::StreamingService& streamingService, QObject* parent) override;

    private:
        Domain::ISettingsStore& _settingsStore;
        Domain::IUserScriptFactory& _userScriptFactory;
        Domain::Players& _players;
        Infrastructure::INetworkProxies& _networkProxies;
        ActiveThemeViewModel& _themeViewModel;
        Infrastructure::IHttpClientFactory& _httpClientFactory;
    };
}

