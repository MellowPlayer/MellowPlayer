#include "QmlTypesSetup.hpp"
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>
#include <QThread>
#include <QtQml/qqml.h>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

QmlTypesSetup::QmlTypesSetup(IQmlSingletons& qmlSingletons) : _qmlSingletons(qmlSingletons)
{
}

void QmlTypesSetup::initialize(const ResultCallback& resultCallback)
{
    qRegisterMetaType<Song*>("Domain::Song*");
    qRegisterMetaType<Song*>("Song*");
    qRegisterMetaType<StreamingService*>("Domain::StreamingService*");
    qRegisterMetaType<StreamingService*>("StreamingService*");
    qRegisterMetaType<ListeningHistoryEntry>("Domain::ListeningHistoryEntry");
    qRegisterMetaType<ListeningHistoryEntry>("ListeningHistoryEntry");
    qRegisterMetaType<Player*>("Domain::Player*");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<SettingViewModel*>("Presentation::SettingViewModel*");
    qRegisterMetaType<SettingViewModel*>("SettingViewModel*");
    qRegisterMetaType<SettingsViewModel*>("SettingsViewModel*");

    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "SettingKey", "SettingKey cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingViewModel>("MellowPlayer", 3, 0, "Setting", "SettingsViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingsViewModel>("MellowPlayer", 3, 0, "SettingsViewModel", "SettingsViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingsCategoryViewModel>("MellowPlayer", 3, 0, "SettingsCategory", "SettingsCategoryViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingListModel>("MellowPlayer", 3, 0, "SettingListModel", "SettingListModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<RemoteControlErrorViewModel>("MellowPlayer", 3, 0, "RemoteControlError", "RemoteControlError cannot be instantiated from QML");
    qmlRegisterUncreatableType<UserScriptsViewModel>("MellowPlayer", 3, 0, "UserScripts", "UserScriptsViewModel cannot be instantiated from QML");
    qmlRegisterUncreatableType<StreamingServiceViewModel>("MellowPlayer", 3, 0, "StreamingService", "StreamingService cannot be instantiated from QML");
    qmlRegisterUncreatableType<StreamingServicesViewModel>("MellowPlayer", 3, 0, "StreamingService", "StreamingService cannot be instantiated from QML");
    qmlRegisterUncreatableType<IPlayer>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");

    _qmlSingletons.registerToQml();

    resultCallback(true);
}
