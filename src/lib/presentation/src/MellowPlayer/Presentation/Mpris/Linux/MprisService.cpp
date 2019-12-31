#include <QtCore>

#include "MellowPlayer/Presentation/Mpris/Linux/Mpris2Player.hpp"
#include "MellowPlayer/Presentation/Mpris/Linux/Mpris2Root.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Mpris/Linux/MprisService.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace std;

QString MprisService::SERVICE_NAME = "org.mpris.MediaPlayer2.";
QString MprisService::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisService::MprisService(IPlayer& player, ILocalAlbumArt& localAlbumArt, IMainWindow& window)
        : _logger(Loggers::logger("Mpris")),
          _parent(make_unique<QObject>()),
          _mpris2Root(new Mpris2Root(window, _parent.get())),
          _mpris2Player(new Mpris2Player(player, localAlbumArt, _parent.get())),
          _serviceName(SERVICE_NAME + qApp->applicationName())
{
}

void MprisService::initialize(const IInitializable::ResultCallback& resultCallback)
{
    resultCallback(start());
}

bool MprisService::start()
{
    if (!QDBusConnection::sessionBus().registerService(_serviceName) || !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, _parent.get()))
    {
        LOG_WARN(_logger, "failed to register service on the session bus: " + _serviceName);
        LOG_WARN(_logger, "failed to register object on the session bus: " + OBJECT_NAME);
        return false;
    }
    LOG_INFO(_logger, "service started: " + _serviceName);
    return true;
}

void MprisService::cleanUp()
{
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(_serviceName);
}

QString MprisService::toString() const
{
    return "Mpris";
}
