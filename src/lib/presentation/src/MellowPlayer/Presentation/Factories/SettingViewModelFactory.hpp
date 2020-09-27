#pragma once

class QObject;

namespace MellowPlayer::Domain
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class ActiveThemeViewModel;
    class SettingViewModel;

    class SettingViewModelFactory
    {
    public:
        explicit SettingViewModelFactory(ActiveThemeViewModel& themeViewModel);
        SettingViewModel* create(Domain::Setting& setting, QObject* parent = nullptr) const;

    private:
        ActiveThemeViewModel& _themeViewModel;
    };
}
