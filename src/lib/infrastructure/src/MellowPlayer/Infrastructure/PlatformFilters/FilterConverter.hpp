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
        QString linux_;
        QString appImage_;
        QString windows_;
        QString osx_;
        QString all_;
    };
}
