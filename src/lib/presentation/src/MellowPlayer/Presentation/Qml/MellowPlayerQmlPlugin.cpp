#include "MellowPlayerQmlPlugin.hpp"
#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Domain/Player/CurrentPlayer.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/RemoteControlViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ScalingFactorSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/TimeLimitSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/UpdateChannelSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <QtQml/qqml.h>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;


void MellowPlayerQmlPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QString("MellowPlayer"));

    qRegisterMetaType<Song*>("Domain::Song*");
    qRegisterMetaType<Song*>("Song*");
    qRegisterMetaType<StreamingService*>("Domain::StreamingService*");
    qRegisterMetaType<StreamingService*>("StreamingService*");
    qRegisterMetaType<ListeningHistoryEntry>("Domain::ListeningHistoryEntry");
    qRegisterMetaType<ListeningHistoryEntry>("ListeningHistoryEntry");
    qRegisterMetaType<Player*>("Domain::Player*");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<IPlayerBase*>("Domain::IPlayerBase*");
    qRegisterMetaType<IPlayerBase*>("IPlayerBase*");
    qRegisterMetaType<SettingViewModel*>("Presentation::SettingViewModel*");
    qRegisterMetaType<SettingViewModel*>("SettingViewModel*");
    qRegisterMetaType<SettingsViewModel*>("SettingsViewModel*");
    qRegisterMetaType<SettingsViewModel*>("SettingsViewModel*");
    qRegisterMetaType<IStreamingServiceViewModel*>("IStreamingServiceViewModel*");
    qRegisterMetaType<StreamingServiceProxyListModel*>("StreamingServiceProxyListModel*");
    qRegisterMetaType<StreamingServiceListModel*>("StreamingServiceListModel*");
    qRegisterMetaType<StreamingServiceListModel*>("StreamingServiceListModel*");
    qRegisterMetaType<NetworkProxy*>("NetworkProxy*");

    qmlRegisterUncreatableType<Song>(uri, 3, 0, "Song", "Song cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingKey>(uri, 3, 0, "SettingKey", "SettingKey cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingViewModel>(uri, 3, 0, "SettingViewModel", "Setting cannot be instantiated from QML");
    qmlRegisterUncreatableType<ColorSettingViewModel>(uri, 3, 0, "ColorSettingViewModel", "ColorSetting cannot be instantiated from QML");
    qmlRegisterUncreatableType<EnumSettingViewModel>(uri, 3, 0, "EnumSettingViewModel", "EnumSetting cannot be instantiated from QML");
    qmlRegisterUncreatableType<TimeLimitSettingViewModel>(uri, 3, 0, "TimeLimitSettingViewModel", "TimeLimitSetting cannot be instantiated from QML");
    qmlRegisterUncreatableType<UpdateChannelSettingViewModel>(uri, 3, 0, "UpdateChannelSettingViewModel", "UpdateChannelSetting cannot be instantiated from QML");
    qmlRegisterUncreatableType<ScalingFactorSettingViewModel>(uri, 3, 0, "ScalingFactorSettingViewModel", "ScalingFactorSetting cannot be instantiated from QML");
    qmlRegisterUncreatableType<ShortcutSettingViewModel>(uri, 3, 0, "ShortcutSettingViewModel", "ScalingFactorSetting cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingsCategoryViewModel>(uri, 3, 0, "SettingsCategoryViewModel", "SettingsCategoryViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingsViewModel>(uri, 3, 0, "SettingsViewModel", "SettingsViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingListModel>(uri, 3, 0, "SettingListModel", "SettingListModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<RemoteControlErrorViewModel>(uri, 3, 0, "RemoteControlErrorViewModel", "RemoteControlError cannot be instantiated from QML");
    qmlRegisterUncreatableType<QQmlObjectListModelBase>(uri, 3, 0, "QQmlObjectListModelBase", "UserScriptsViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<IUserScriptsViewModel>(uri, 3, 0, "IUserScriptsViewModel", "UserScriptsViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<IStreamingServiceViewModel>(uri, 3, 0, "StreamingServiceViewModel", "StreamingService cannot be instantiated from QML");
    qmlRegisterType<NullStreamingServiceViewModel>(uri, 3, 0, "NullStreamingServiceViewModel");
    qmlRegisterUncreatableType<IPlayerBase>(uri, 3, 0, "IPlayerBase", "Player cannot be instantiated from QML");
    qmlRegisterUncreatableType<StreamingServiceProxyListModel>(uri, 3, 0, "StreamingServiceProxyListModel", "StreamingServiceProxyListModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<StreamingServiceListModel>(uri, 3, 0, "StreamingServiceListModel", "StreamingServiceListModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<ListeningHistoryProxyListModel>(uri, 3, 0, "ListeningHistoryProxyListModel", "ListeningHistoryProxyListModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<RemoteControlApplicationInfoViewModel>(uri, 3, 0, "RemoteControlApplicationInfoViewModel", "RemoteControlApplicationInfo cannot be instantiated from QML");
    qmlRegisterUncreatableType<ZoomViewModel>(uri, 3, 0, "ZoomViewModel", "ZoomViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<RunningServicesViewModel>(uri, 3, 0, "RunningServicesViewModel", "ZoomViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<IMainWindow>(uri, 3, 0, "IMainWindow", "IMainWindow cannot be instantiated from QML");
    qmlRegisterUncreatableType<NetworkProxy>(uri, 3, 0, "NetworkProxy", "NetworkProxy cannot be instantiated from QML");

    // Singletons
    qmlRegisterUncreatableType<CurrentPlayer>(uri, 3, 0, "CurrentPlayer", "CurrentPlayer cannot be instantiated from QML");
    qmlRegisterUncreatableType<StreamingServicesViewModel>(uri, 3, 0, "StreamingServicesViewModel", "StreamingServicesViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<ListeningHistoryViewModel>(uri, 3, 0, "ListeningHistoryViewModel", "ListeningHistoryViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<ThemeViewModel>(uri, 3, 0, "ThemeViewModel", "ThemeViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<RemoteControlViewModel>(uri, 3, 0, "RemoteControlViewModel", "RemoteControl cannot be instantiated from QML");
    qmlRegisterUncreatableType<MainWindowViewModel>(uri, 3, 0, "MainWindowViewModel", "MainWindowViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<ClipBoardViewModel>(uri, 3, 0, "ClipBoardViewModel", "ApplicationViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<ApplicationViewModel>(uri, 3, 0, "ApplicationViewModel", "ApplicationViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<UpdaterViewModel>(uri, 3, 0, "UpdaterViewModel", "Updater cannot be instantiated from QML");
    qmlRegisterUncreatableType<DevToolsWindowViewModel>(uri, 3, 0, "DevToolsWindowViewModel", "DevToolsWindow cannot be instantiated from QML");
}

void MellowPlayerQmlPlugin::initializeEngine(QQmlEngine*, const char*)
{
    auto qmlSingletons = IQmlSingletons::instance();
    if (qmlSingletons != nullptr)
        qmlSingletons->registerToQml();
}
