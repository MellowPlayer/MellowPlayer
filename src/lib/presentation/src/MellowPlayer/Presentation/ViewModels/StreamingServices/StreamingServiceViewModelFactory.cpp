#include "StreamingServiceViewModelFactory.hpp"
#include <MellowPlayer/Infrastructure/Network/IHttpClientFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

StreamingServiceViewModelFactory::StreamingServiceViewModelFactory(ISettingsStore& settingsStore,
                                                                   IUserScriptFactory& userScriptFactory,
                                                                   Players& players,
                                                                   INetworkProxies& networkProxies,
                                                                   ActiveThemeViewModel& themeViewModel,
                                                                   IHttpClientFactory& httpClientFactory)
        : _settingsStore(settingsStore),
          _userScriptFactory(userScriptFactory),
          _players(players),
          _networkProxies(networkProxies),
          _themeViewModel(themeViewModel),
          _httpClientFactory(httpClientFactory)
{
}

StreamingServiceViewModel* StreamingServiceViewModelFactory::create(StreamingService& streamingService, QObject* parent)
{
    return new StreamingServiceViewModel(
            streamingService, _settingsStore, _userScriptFactory, _players, _networkProxies, _themeViewModel, _httpClientFactory.create(), parent);
}
