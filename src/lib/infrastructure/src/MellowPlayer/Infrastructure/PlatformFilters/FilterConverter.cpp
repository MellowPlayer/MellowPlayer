#include <MellowPlayer/Infrastructure/PlatformFilters/FilterConverter.hpp>

using namespace MellowPlayer::Infrastructure;

FilterConverter::FilterConverter() : _linux("Linux"), _windows("Windows"), _osx("OSX"), _all("All")
{
}

QString FilterConverter::toString(Filter filter) const
{
    QString filterString;

    switch (filter)
    {
    case Filter::Linux:
        filterString = _linux;
        break;
    case Filter::OSX:
        filterString = _osx;
        break;
    case Filter::Windows:
        filterString = _windows;
        break;
    case Filter::All:
        filterString = _all;
        break;
    }

    return filterString;
}

Filter FilterConverter::fromString(const QString& filterString) const
{
    QString lowerCaseFilter = filterString.toLower().trimmed();

    if (lowerCaseFilter == _linux.toLower())
        return Filter::Linux;
    else if (lowerCaseFilter == _windows.toLower())
        return Filter::Windows;
    else if (lowerCaseFilter == _osx.toLower())
        return Filter::OSX;
    else
        return Filter::All;
}
