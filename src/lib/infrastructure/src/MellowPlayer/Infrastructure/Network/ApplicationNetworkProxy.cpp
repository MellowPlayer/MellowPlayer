#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/Network/ApplicationNetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

ApplicationNetworkProxy::ApplicationNetworkProxy(StreamingServices& streamingServices, INetworkProxies& networkProxies)
        : _logger(Loggers::logger("ApplicationNetworkProxy")),
          _initialNetworkProxy(QNetworkProxy::applicationProxy()),
          _streamingServices(streamingServices),
          _networkProxies(networkProxies)
{
    connect(&streamingServices, &StreamingServices::currentChanged, this, &ApplicationNetworkProxy::onCurrentStreamingServiceChanged);
}

void ApplicationNetworkProxy::onCurrentStreamingServiceChanged(StreamingService* service)
{
    if (_currentNetworkProxy)
        disconnect(_currentNetworkProxy.get(), &NetworkProxy::changed, this, &ApplicationNetworkProxy::updateNetworkProxy);

    if (service != nullptr)
    {
        _currentServiceName = service->name();
        _currentNetworkProxy = _networkProxies.get(service->name());
        connect(_currentNetworkProxy.get(), &NetworkProxy::changed, this, &ApplicationNetworkProxy::updateNetworkProxy);
    }
    else
        _currentNetworkProxy = nullptr;

    updateNetworkProxy();
}

void ApplicationNetworkProxy::updateNetworkProxy()
{
    if (_currentNetworkProxy != nullptr && _currentNetworkProxy->isValid())
    {
        LOG_INFO(_logger, QString("Using %1 network proxy settings: _%2").arg(_currentServiceName).arg(_currentNetworkProxy->toString()));
        QNetworkProxy::setApplicationProxy(_currentNetworkProxy->create());
    }
    else if (QNetworkProxy::applicationProxy() != _initialNetworkProxy)
    {
        LOG_INFO(_logger, "Restoring initial network proxy");
        QNetworkProxy::setApplicationProxy(_initialNetworkProxy);
    }
}

ApplicationNetworkProxy::~ApplicationNetworkProxy()
{
    QNetworkProxy::setApplicationProxy(_initialNetworkProxy);
}
