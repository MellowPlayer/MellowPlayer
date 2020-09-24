#pragma once

#include <cmath>
#include <QColor>
#include <MellowPlayer/Domain/Theme/IThemeLoader.hpp>
#include <MellowPlayer/Domain/Theme/Theme.hpp>

namespace MellowPlayer::Domain
{
    class FakeThemeLoader : public IThemeLoader
    {
    public:
        Theme load(const QString&) const override
        {
            {
                auto makePalette = [](int count) {
                    QVector<QColor> colors;
                    float currentHue = 0.0;
                    for (int i = 0; i < count; i++)
                    {
                        colors.push_back(QColor::fromHslF(currentHue, 1.0, 0.5));
                        currentHue += 0.618033988749895f;
                        currentHue = std::fmod(currentHue, 1.0f);
                    }
                    return colors;
                };

                auto colorPalette = makePalette(7);

                Theme theme;
                theme.accent = colorPalette[0].name();
                theme.background = colorPalette[1].name();
                theme.foreground = colorPalette[2].name();
                theme.primary = colorPalette[3].name();
                theme.primaryForeground = colorPalette[4].name();
                theme.secondary = colorPalette[5].name();
                theme.secondaryForeground = colorPalette[6].name();

                return theme;
            }
        }
    };
}