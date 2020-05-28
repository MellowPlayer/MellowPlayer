#include <QtCore>

#include "MellowPlayer/Presentation/Mpris/Linux/Mpris2Player.hpp"
#include "MellowPlayer/Presentation/Mpris/Linux/Mpris2Root.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Mpris/Linux/MprisStartup.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace std;

QString MprisStartup::SERVICE_NAME = "org.mpris.MediaPlayer2.";
QString MprisStartup::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisStartup::MprisStartup(IPlayer& player, ILocalAlbumArt& localAlbumArt, IMainWindow& window)
        : _logger(Loggers::logger("Mpris")),
          _parent(make_unique<QObject>()),
          _player(player),
          _localAlbumArt(localAlbumArt),
          _window(window),
          _serviceName(SERVICE_NAME + qApp->applicationName())
{
}

void MprisStartup::initialize(const Initializable::ResultCallback& resultCallback)
{
    start();
    resultCallback(true);
}

bool MprisStartup::start()
{

    if (!QDBusConnection::sessionBus().registerService(_serviceName) || !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, _parent.get()))
    {
        LOG_WARN(_logger, "failed to register service on the session bus: " + _serviceName);
        LOG_WARN(_logger, "failed to register object on the session bus: " + OBJECT_NAME);
        return false;
    }
    _mpris2Root = new Mpris2Root(_window, _parent.get());
    _mpris2Player = new Mpris2Player(_player, _localAlbumArt, _parent.get());
    LOG_DEBUG(_logger, "service started: " + _serviceName);
    return true;
}

void MprisStartup::cleanUp()
{
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(_serviceName);
}