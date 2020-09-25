#include "QmlTypesSetup.hpp"
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <QThread>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

QmlTypesSetup::QmlTypesSetup(ApplicationViewModel&,
                             SettingsViewModel&,
                             UpdaterViewModel&,
                             ListeningHistoryViewModel&,
                             ZoomViewModel&,
                             RemoteControlViewModel&,
                             IContextProperties& contextProperties)
        : _cacheViewModel(contextProperties),
          _cookiesViewModel(contextProperties),
          _clipBoardViewModel(contextProperties),
          _devToolWindowViewModel(contextProperties),
          _contextProperties(contextProperties)
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
