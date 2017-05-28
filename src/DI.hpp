#pragma once

#include <boost/di.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <MellowPlayer/UseCases/Interfaces/IStreamingServicePluginLoader.hpp>
#include <MellowPlayer/UseCases/Interfaces/IAlbumArtDownloader.hpp>
#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include <MellowPlayer/UseCases/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/UseCases/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/UseCases/Interfaces/IAlbumArtDownloader.hpp>
#include <MellowPlayer/UseCases/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/UseCases/Interfaces/ISystemTrayIcon.hpp>
#include <MellowPlayer/UseCases/Interfaces/IListeningHistoryDataProvider.hpp>
#include <MellowPlayer/UseCases/Interfaces/ILocalAlbumArtService.hpp>
#include <MellowPlayer/UseCases/Interfaces/INotificationsService.hpp>
#include <MellowPlayer/UseCases/Interfaces/IHotkeysService.hpp>
#include <MellowPlayer/UseCases/Interfaces/IMprisService.hpp>
#include <MellowPlayer/UseCases/Player/IPlayer.hpp>
#include <MellowPlayer/UseCases/Player/PlayerProxy.hpp>
#include <MellowPlayer/UseCases/Services/PlayerService.hpp>
#include <MellowPlayer/UseCases/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/UseCases/Services/ListeningHistoryService.hpp>
#include <MellowPlayer/Presentation/Notifications/NotificationService.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/LibnotifyPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SnorenotifyPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceStyleModel.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp>
#include <MellowPlayer/Presentation/Models/MainWindowModel.hpp>
#include <MellowPlayer/Presentation/SystemTrayIcon.hpp>
#include <MellowPlayer/Infrastructure/AlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServicePluginLoader.hpp>
#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Applications/Application.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/SqlLiteListeningHistoryDataProvider.hpp>
#include <MellowPlayer/Infrastructure/Services/HotkeysService.hpp>
#include <MellowPlayer/Infrastructure/Services/LocalAlbumArtService.hpp>

#ifdef USE_SNORENOTIFY
    #include <MellowPlayer/Presentation/Notifications/Presenters/SnorenotifyPresenter.hpp>
#endif

#ifdef Q_OS_LINUX
    #include <MellowPlayer/Infrastructure/Services/MprisService.hpp>
    #include <MellowPlayer/Infrastructure/Applications/LinuxApplication.hpp>
#endif


USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

namespace di = boost::di;

/**
 * http://boost-experimental.github.io/di/extensions/index.html#scoped-scope
 */
class ScopedScope {
public:
    template <class, class T>
    class scope {
    public:
        template <class T_>
        using is_referable = typename di::wrappers::shared<ScopedScope, T>::template is_referable<T_>;

        template <class, class, class TProvider, class T_ = di::aux::decay_t<decltype(di::aux::declval<TProvider>().get())>>
        static decltype(di::wrappers::shared<ScopedScope, T_>{
            std::shared_ptr<T_>{std::shared_ptr<T_>{di::aux::declval<TProvider>().get()}}})
        try_create(const TProvider &);

        template <class T_, class, class TProvider>
        auto create(const TProvider &provider) {
            return create_impl<di::aux::decay_t<decltype(provider.get())>>(provider);
        }

        scope() = default;
        scope(scope &&other) noexcept : object_(other.object_) { other.object_ = nullptr; }
        ~scope() noexcept { delete object_; }

    private:
        template <class, class TProvider>
        auto create_impl(const TProvider &provider) {
            if (!object_) {
                object_ = new std::shared_ptr<T>{provider.get()};
            }
            return di::wrappers::shared<ScopedScope, T, std::shared_ptr<T> &>{*object_};
        }

        std::shared_ptr<T> *object_ = nullptr;
    };
};

auto defaultInjector = [](ScopedScope& scope) {
    return di::make_injector(
        di::bind<IStreamingServicePluginLoader>().to<StreamingServicePluginLoader>().in(scope),
        di::bind<IPlayer>().in(di::singleton).to<PlayerProxy>(),
        di::bind<IAlbumArtDownloader>().to<AlbumArtDownloader>().in(scope),
        di::bind<IMainWindow>().to<MellowPlayer::Presentation::MainWindowModel>().in(scope),
        di::bind<ILocalAlbumArtService>().to<LocalAlbumArtService>().in(scope),
        di::bind<IHotkeysService>().to<HotkeysService>().in(scope),
        di::bind<ISystemTrayIcon>().to<SystemTrayIcon>().in(scope),
        di::bind<IListeningHistoryDataProvider>().to<SqlLiteListeningHistoryDataProvider>().in(scope),
        di::bind<INotificationService>().to<NotificationService>().in(scope),
        di::bind<ISettingsProvider>().to<QSettingsProvider>().in(scope),
        di::bind<IWorkDispatcher>().to<QtConcurrentWorkDispatcher>().in(scope),
        di::bind<ISettingsSchemaLoader>().to<SettingsSchemaLoader>().in(scope)
    );
};

auto platformInjector = [](ScopedScope& scope) {
#ifdef Q_OS_LINUX
    return di::make_injector(
            di::bind<IMprisService>().to<MprisService>().in(scope),
            di::bind<IApplication>().to<LinuxApplication>().in(scope)
    );
#else
    return di::make_injector(
        di::bind<IApplication>().to<Application>().in(scope)
    );
#endif
};

auto notificationPresenterInjector = [](ScopedScope& scope) {
#if defined(USE_SNORENOTIFY)
    return di::make_injector(
        di::bind<INotificationPresenter>().to<SnorenotifyPresenter>().in(scope)
    );
#elif defined(USE_LIBNOTIFY)
    return di::make_injector(
            di::bind<INotificationPresenter>().to<LibnotifyPresenter>().in(scope)
    );
#else
    return di::make_injector(
            di::bind<INotificationPresenter>().to<SystemTrayIconPresenter>().in(scope)
    );
#endif
};