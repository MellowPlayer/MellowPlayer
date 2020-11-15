#pragma once

#include "Filter.hpp"
#include <QString>

namespace MellowPlayer::Infrastructure
{
    class FilterConverter
    {
    public:
        FilterConverter();

        QString toString(Filter filter) const;
        Filter fromString(const QString& filterString) const;

    private:
        QString _linux;
        QString _windows;
        QString _osx;
        QString _all;
    };
}
