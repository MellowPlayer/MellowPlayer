#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

NetworkProxies::NetworkProxies(ISettingsStore& settingsStore, StreamingServices& streamingServices)
        : _settingsStore(settingsStore), _streamingServices(streamingServices)
{
    connect(&streamingServices, &StreamingServices::added, this, &NetworkProxies::onStreamingServiceAdded);
}

std::shared_ptr<NetworkProxy> NetworkProxies::get(const QString& name) const
{
    return _items[name];
}

void NetworkProxies::onStreamingServiceAdded(StreamingService* service)
{
    add(service->name(), make_shared<NetworkProxy>(_settingsStore.value(settingUrl(service->name())).toMap()));
}

void NetworkProxies::add(const QString& serviceName, const shared_ptr<NetworkProxy>& networkProxy)
{
    _items[serviceName] = networkProxy;
    connect(networkProxy.get(), &NetworkProxy::changed, [=]() { _settingsStore.setValue(settingUrl(serviceName), networkProxy->toQVariantMap()); });
}

QString NetworkProxies::settingUrl(const QString& name) const
{
    return name + "/networkProxy";
}
