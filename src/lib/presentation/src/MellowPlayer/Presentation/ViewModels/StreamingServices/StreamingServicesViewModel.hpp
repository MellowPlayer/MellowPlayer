#pragma once

#include <MellowPlayer/Presentation/Models/StreamingServiceListModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

class QQmlApplicationEngine;

namespace MellowPlayer::Domain
{
    class Settings;
    class Setting;
    class Players;
    class StreamingServices;
    class StreamingService;
    class IWorkDispatcher;
    class IStreamingServiceCreator;
    class IUserScriptFactory;
}

namespace MellowPlayer::Infrastructure
{
    class ICommandLineArguments;
    class INetworkProxies;
    class IHttpClientFactory;
}

namespace MellowPlayer::Presentation
{
    class IStreamingServiceViewModelFactory;

    class IStreamingServicesViewModel : public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(StreamingServiceProxyListModel* filteredServices READ filteredServices CONSTANT)
        Q_PROPERTY(StreamingServiceViewModel* currentService READ currentService WRITE setCurrentService NOTIFY currentServiceChanged)
        Q_PROPERTY(QString currentServiceName READ currentServiceName NOTIFY currentServiceNameChanged)
    public:
        using QmlSingleton::QmlSingleton;

        virtual void initialize() = 0;
        virtual QList<StreamingServiceViewModel*> services() const = 0;
        virtual StreamingServiceProxyListModel* filteredServices() = 0;
        virtual StreamingServiceViewModel* currentService() const = 0;

        virtual QString currentServiceName() const = 0;
        virtual Q_INVOKABLE void reload() = 0;
        virtual Q_INVOKABLE void next() = 0;
        virtual Q_INVOKABLE void previous() = 0;
        virtual Q_INVOKABLE void setCurrentService(StreamingServiceViewModel* value) = 0;
        virtual Q_INVOKABLE void createService(const QString& serviceName,
                                               const QString& serviceUrl,
                                               const QString& authorName,
                                               const QString& authorWebsite,
                                               bool allPlatforms,
                                               bool linuxPlatform,
                                               bool appImagePlatform,
                                               bool osxPlatform,
                                               bool windowsPlatform) = 0;

    signals:
        void currentServiceChanged();
        void currentServiceNameChanged();
        void serviceCreated(const QString& directory);
    };

    class StreamingServicesViewModel : public IStreamingServicesViewModel
    {
        Q_OBJECT
    public:
        StreamingServicesViewModel(Domain::StreamingServices& streamingServices,
                                   Domain::Settings& settings,
                                   Domain::IWorkDispatcher& workDispatcher,
                                   Domain::IStreamingServiceCreator& streamingServiceCreator,
                                   Infrastructure::ICommandLineArguments& commandLineArguments,
                                   IStreamingServiceViewModelFactory& streamingServiceViewModelFactory);

        void initialize() override;

        QList<StreamingServiceViewModel*> services() const override;
        StreamingServiceProxyListModel* filteredServices() override;
        StreamingServiceViewModel* currentService() const override;

        QString currentServiceName() const override;

        Q_INVOKABLE void reload() override;
        Q_INVOKABLE void next() override;
        Q_INVOKABLE void previous() override;
        Q_INVOKABLE void setCurrentService(StreamingServiceViewModel* value) override;
        Q_INVOKABLE void createService(const QString& serviceName,
                                       const QString& serviceUrl,
                                       const QString& authorName,
                                       const QString& authorWebsite,
                                       bool allPlatforms,
                                       bool linuxPlatform,
                                       bool appImagePlatform,
                                       bool osxPlatform,
                                       bool windowsPlatform) override;

        void registerTo(IQmlApplicationEngine& qmlApplicationEngine) override;

    signals:
        void serviceCreated(const QString& directory);

    private slots:
        void onServiceAdded(Domain::StreamingService* streamingService);
        void onCurrentServiceChanged(Domain::StreamingService* value);

    private:
        int nextIndex(int index) const;
        int previousIndex(int index) const;

        Domain::StreamingServices& _streamingServices;
        Domain::Settings& _settings;
        Domain::Setting& _currentServiceSetting;
        Domain::IWorkDispatcher& _workDispatcher;
        Domain::IStreamingServiceCreator& _streamingServiceCreator;
        Infrastructure::ICommandLineArguments& _commandLineArguments;
        IStreamingServiceViewModelFactory& _streamingServiceViewModelFactory;
        StreamingServiceListModel* _services;
        StreamingServiceProxyListModel _filteredServices;
        StreamingServiceViewModel* _currentService = nullptr;
        void initializeCurrent();
        void load();
    };
}
