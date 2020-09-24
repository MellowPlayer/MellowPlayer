#include <MellowPlayer/Infrastructure/Updater/Asset.hpp>
#include <QUrl>

using namespace MellowPlayer::Infrastructure;

Asset::Asset() : Asset("", "")
{
}

Asset::Asset(const QString& name, const QString& url) : _name(name), _url(url)
{
}

QString Asset::name() const
{
    return _name;
}

QString Asset::url() const
{
    return _url;
}

bool Asset::isAppImage() const
{
    return _name.toLower().endsWith(".appimage");
}

bool Asset::isWindowsInstaller() const
{
    return _name.toLower().endsWith("_setup.exe");
}

bool Asset::isDmg() const
{
    return _name.endsWith(".dmg");
}

bool Asset::isValid() const
{
    return QUrl(_url).isValid() && (isAppImage() || isWindowsInstaller() || isDmg());
}
