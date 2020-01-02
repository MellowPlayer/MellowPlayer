#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

StreamingServices::StreamingServices(IStreamingServiceLoader& loader, IStreamingServiceWatcher& watcher)
        : _logger(Loggers::logger("StreamingServices")), _loader(loader), _watcher(watcher), _current(nullptr)
{
}

void StreamingServices::load()
{
    auto newServices = _loader.load();

    for (auto newService : newServices)
    {
        bool found = false;
        for (auto service : _services)
        {
            if (*service == *newService)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            LOG_DEBUG(_logger, "service added: " + newService->name());
            _services.append(newService);
            if (!newService->pluginDirectory().startsWith("/usr/") && !newService->pluginDirectory().startsWith("/tmp/"))
                _watcher.watch(*newService);
            emit added(newService.get());
        }
    }
}

StreamingService& StreamingServices::get(const QString& name) const
{
    for (const auto& service : _services)
        if (service->name() == name)
            return *service;
    throw invalid_argument("unknown service: " + name.toStdString());
}

void StreamingServices::setCurrent(StreamingService* service)
{
    if (service == _current)
        return;

    _current = service;
    emit currentChanged(_current);
    if (_current)
        LOG_INFO(_logger, "current service changed: " + _current->name());
}

StreamingService* StreamingServices::current() const
{
    return _current;
}
