#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Mpris/Linux/Mpris2Root.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

Mpris2Root::Mpris2Root(IMainWindow& mainWindow, QObject* parent) : QDBusAbstractAdaptor(parent), _logger(Loggers::logger("Mpris2Root")), _mainWindow(mainWindow)
{
}

void Mpris2Root::Raise()
{
    _mainWindow.raise();
}

void Mpris2Root::Quit()
{
    _mainWindow.requestQuit();
}

bool Mpris2Root::canRaise()
{
    return true;
}

bool Mpris2Root::canQuit()
{
    return true;
}

bool Mpris2Root::hasTrackList()
{
    return false;
}

bool Mpris2Root::canSetFullscreen()
{
    return false;
}

bool Mpris2Root::fullscreen()
{
    return false;
}

void Mpris2Root::setFullscreen(bool value)
{
    Q_UNUSED(value);
}

QString Mpris2Root::identity()
{
    return "MellowPlayer";
}

QString Mpris2Root::desktopEntry()
{
    return "mellowplayer";
}

QStringList Mpris2Root::supportedUriSchemes()
{
    return QStringList();
}

QStringList Mpris2Root::supportedMimeTypes()
{
    return QStringList();
}
