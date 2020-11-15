#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>

using namespace MellowPlayer::Infrastructure;

Release Release::current_(BuildConfig::getVersion(), QDate::fromString(BuildConfig::getBuildDate(), Qt::ISODate));

Release::Release(const QString& name, const QDate& date, QObject* parent) : QObject(parent), _url(""), _name(name), _date(date), _preRelease(false), _assets()
{
}

Release::Release(const QString& url, const QString& name, const QDate& date, const AssetList& assets, bool preRelease, QObject* parent)
        : QObject(parent), _url(url), _name(name), _date(date), _preRelease(preRelease), _assets(assets)
{
}

QString Release::url() const
{
    return _url;
}

QString Release::name() const
{
    return _name;
}

QString Release::date() const
{
    return _date.toString("MMMM dd yyyy");
}

bool Release::isPreRelease() const
{
    return _preRelease;
}

const AssetList& Release::assets() const
{
    return _assets;
}

bool Release::operator==(const Release& other) const
{
    return _date == other._date;
}

bool Release::operator!=(const Release& other) const
{
    return !operator==(other);
}

bool Release::operator>(const Release& other) const
{
    return _date > other._date;
}

bool Release::operator>=(const Release& other) const
{
    return _date >= other._date;
}

bool Release::operator<(const Release& other) const
{
    return _date < other._date;
}

bool Release::operator<=(const Release& other) const
{
    return _date <= other._date;
}

const Release& Release::current()
{
    return current_;
}

bool Release::isValid() const
{
    bool isValid = !date().isEmpty() && !name().isEmpty();

    if (isValid && !_url.isEmpty())
    {
        bool haveWindowsInstaller = false;
        bool haveDmg = false;

        for (auto& asset : _assets)
        {
            if (asset.isDmg())
                haveDmg = true;
            if (asset.isWindowsInstaller())
                haveWindowsInstaller = true;
        }

        return haveDmg && haveWindowsInstaller;
    }

    return isValid;
}
