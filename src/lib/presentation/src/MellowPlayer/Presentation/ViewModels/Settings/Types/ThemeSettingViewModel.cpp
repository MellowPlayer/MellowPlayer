#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ThemeSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ThemeSettingViewModel::ThemeSettingViewModel(Setting& setting, QObject* parent, ThemeViewModel& themeViewModel)
        : EnumSettingViewModel(setting, parent), _themeViewModel(themeViewModel)
{
}

QStringList ThemeSettingViewModel::values() const
{
    return _themeViewModel.availableThemes();
}
