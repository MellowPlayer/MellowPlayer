#pragma once

#include "EnumSettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class ActiveThemeViewModel;

    class ThemeSettingViewModel : public EnumSettingViewModel
    {
        Q_OBJECT
    public:
        ThemeSettingViewModel(Domain::Setting& setting, QObject* parent, ActiveThemeViewModel& themeViewModel);
        QStringList values() const override;

    private:
        ActiveThemeViewModel& _themeViewModel;
    };
}
