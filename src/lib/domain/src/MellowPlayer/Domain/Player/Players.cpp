#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

Players::Players(StreamingServices& streamingServices)
{
    connect(&streamingServices, &StreamingServices::added, this, &Players::onServiceAdded);
    for (auto& service : streamingServices.toList())
    {
        onServiceAdded(service.get());
    }
}

shared_ptr<Player> Players::get(const QString& serviceName) const
{
    return _players[serviceName];
}

void Players::onServiceAdded(StreamingService* service)
{
    if (!_players.contains(service->name()))
        _players[service->name()] = make_shared<Player>(*service);
}
