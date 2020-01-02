#include "QmlTypesSetup.hpp"
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <QtCore/QThread>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

QmlTypesSetup::QmlTypesSetup(ApplicationViewModel&,
                             IMainWindow&,
                             SettingsViewModel&,
                             ThemeViewModel&,
                             UpdaterViewModel&,
                             ListeningHistoryViewModel&,
                             StreamingServicesViewModel&,
                             ZoomViewModel&,
                             CacheViewModel&,
                             CookiesViewModel&,
                             ClipBoardViewModel&,
                             DevToolsWindowViewModel&,
                             IContextProperties& contextProperties)
        : _contextProperties(contextProperties)
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

    _contextProperties.registerToQml();

    resultCallback(true);
}
