#pragma once

#include <QString>

namespace MellowPlayer::Domain
{
    struct Theme;

    class IThemeLoader
    {
    public:
        virtual ~IThemeLoader() = default;

        virtual Theme load(const QString& path) const = 0;
    };
}