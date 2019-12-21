#include <MellowPlayer/Infrastructure/PlatformFilters/FilterConverter.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/TokenizedFilters.hpp>

using namespace MellowPlayer::Infrastructure;

#define PLATFORM_FILTER_SEPARATOR "-"

TokenizedFilters::TokenizedFilters(const QString& filters)
{
    QStringList tokens = filters.toLower().split(PLATFORM_FILTER_SEPARATOR);
    FilterConverter converter;

    for (auto token : tokens)
        _filters.append(converter.fromString(token));
}

TokenizedFilters::TokenizedFilters(const QList<Filter>& filters) : _filters(filters)
{
}

QString TokenizedFilters::join() const
{
    QStringList strings;
    FilterConverter converter;

    for (auto filter : _filters)
    {
        strings.append(converter.toString(filter));
    }

    return strings.join(PLATFORM_FILTER_SEPARATOR);
}

TokenizedFilters::const_iterator TokenizedFilters::begin(void) const
{
    return _filters.begin();
}

TokenizedFilters::const_iterator TokenizedFilters::end(void) const
{
    return _filters.end();
}
