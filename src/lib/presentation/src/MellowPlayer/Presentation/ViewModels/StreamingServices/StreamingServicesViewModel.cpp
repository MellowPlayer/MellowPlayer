#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/TokenizedFilters.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;

StreamingServicesViewModel::StreamingServicesViewModel(StreamingServices& streamingServices,
                                                       Players& players,
                                                       Settings& settings,
                                                       IWorkDispatcher& workDispatcher,
                                                       IStreamingServiceCreator& streamingServiceCreator,
                                                       ICommandLineArguments& commandLineArguments,
                                                       IUserScriptFactory& userScriptFactory,
                                                       std::shared_ptr<IContextProperties> contextProperties,
                                                       INetworkProxies& networkProxies,
                                                       ThemeViewModel& themeViewModel)
        : ContextProperty("streamingServices", this, contextProperties),
          _streamingServices(streamingServices),
          _players(players),
          _settings(settings),
          _currentServiceSetting(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
          _workDispatcher(workDispatcher),
          _streamingServiceCreator(streamingServiceCreator),
          _commandLineArguments(commandLineArguments),
          _userScriptFactory(userScriptFactory),
          _networkProxies(networkProxies),
          _allServices(new StreamingServiceListModel(this, QByteArray(), "name")),
          _enabledServices(_allServices),
          _themeViewModel(themeViewModel)
{
}

void StreamingServicesViewModel::initialize()
{
    _streamingServices.load();
    for (auto& service : _streamingServices.toList())
    {
        onServiceAdded(service.get());
    }

    connect(&_streamingServices, &StreamingServices::added, this, &StreamingServicesViewModel::onServiceAdded);

    auto currentServiceName = _currentServiceSetting.value().toString();
    if (!_commandLineArguments.service().isEmpty())
        currentServiceName = _commandLineArguments.service();
    for (auto service : _allServices->toList())
    {
        if (service->name().toLower() == currentServiceName.toLower())
            setCurrentService(service);
    }
}

StreamingServiceViewModel* StreamingServicesViewModel::currentService() const
{
    return _currentService;
}

void StreamingServicesViewModel::setCurrentService(QObject* value)
{
    if (_currentService == value)
        return;

    _currentService = static_cast<StreamingServiceViewModel*>(value);
    if (_currentService == nullptr)
    {
        _currentServiceSetting.setValue("");
        _streamingServices.setCurrent(nullptr);
    }
    else
    {
        _currentServiceSetting.setValue(_currentService->name());
        _streamingServices.setCurrent(_currentService->streamingService());
    }

    emit currentServiceChanged(_currentService);
}

void StreamingServicesViewModel::reload()
{
    _streamingServices.load();
}

void StreamingServicesViewModel::onServiceAdded(StreamingService* streamingService)
{
    auto* sv = new StreamingServiceViewModel(*streamingService, _settings.store(), _userScriptFactory, _players, _networkProxies, _themeViewModel, this);
    _allServices->append(sv);
}

void StreamingServicesViewModel::next()
{
    int currentIndex = _allServices->indexOf(_currentService);
    int index = nextIndex(currentIndex);

    while (index != currentIndex)
    {
        auto* sv = _allServices->at(index);
        if (sv->isActive() && sv->isEnabled())
        {
            setCurrentService(sv);
            break;
        }
        index = nextIndex(index);
    }
}

void StreamingServicesViewModel::previous()
{
    int currentIndex = _allServices->indexOf(_currentService);
    int index = previousIndex(currentIndex);

    while (index != currentIndex)
    {
        auto* sv = _allServices->at(index);
        if (sv->isActive() && sv->isEnabled())
        {
            setCurrentService(sv);
            break;
        }
        index = previousIndex(index);
    }
}

void StreamingServicesViewModel::createService(const QString& serviceName,
                                               const QString& serviceUrl,
                                               const QString& authorName,
                                               const QString& authorWebsite,
                                               bool allPlatforms,
                                               bool linuxPlatform,
                                               bool appImagePlatform,
                                               bool osxPlatform,
                                               bool windowsPlatform)
{
    QList<Filter> filters;
    if (allPlatforms)
        filters.append(Filter::All);
    else
    {
        if (linuxPlatform)
            filters.append(Filter::Linux);

        if (appImagePlatform)
            filters.append(Filter::AppImage);

        if (osxPlatform)
            filters.append(Filter::OSX);

        if (windowsPlatform)
            filters.append(Filter::Windows);
    }
    TokenizedFilters tokenizedFilters(filters);
    _workDispatcher.invoke([=]() {
        QString pluginDir = _streamingServiceCreator.create(serviceName, serviceUrl, authorName, authorWebsite, tokenizedFilters.join());
        emit serviceCreated(pluginDir);
        _streamingServices.load();
    });
}

int StreamingServicesViewModel::nextIndex(int index) const
{
    int nextIndex = index + 1;
    if (nextIndex >= _allServices->count())
        nextIndex = 0;
    return nextIndex;
}

int StreamingServicesViewModel::previousIndex(int index) const
{
    int previousIndex = index - 1;
    if (previousIndex < 0)
        previousIndex = _allServices->count() - 1;
    return previousIndex;
}

StreamingServiceListModel* StreamingServicesViewModel::allServices()
{
    return _allServices;
}
StreamingServiceProxyListModel* StreamingServicesViewModel::enabledServices()
{
    return &_enabledServices;
}

void StreamingServicesViewModel::initialize(IQmlApplicationEngine& qmlApplicationEngine)
{
    qRegisterMetaType<Infrastructure::NetworkProxy*>("Infrastructure::NetworkProxy*");
    ContextProperty::initialize(qmlApplicationEngine);
}
