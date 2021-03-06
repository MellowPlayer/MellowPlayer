#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/IconSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ScalingFactorSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ThemeSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/TimeLimitSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/UpdateChannelSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/UserAgentStringSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

SettingViewModelFactory::SettingViewModelFactory(ThemeViewModel& themeViewModel) : _themeViewModel(themeViewModel)
{
}

SettingViewModel* SettingViewModelFactory::create(Setting& setting, QObject* parent) const
{
    QString type = setting.type().toLower();
    if (type == "bool")
        return new BoolSettingViewModel(setting, parent);
    else if (type == "color")
        return new ColorSettingViewModel(setting, parent);
    else if (type == "shortcut")
        return new ShortcutSettingViewModel(setting, parent);
    else if (type.startsWith("enum"))
        return new EnumSettingViewModel(setting, parent);
    else if (type.startsWith("time-limit"))
        return new TimeLimitSettingViewModel(setting, parent);
    else if (type.startsWith("update-channel"))
        return new UpdateChannelSettingViewModel(setting, parent);
    else if (type.startsWith("theme"))
        return new ThemeSettingViewModel(setting, parent, _themeViewModel);
    else if (type.startsWith("user-agent"))
        return new UserAgentStringSettingViewModel(setting, parent);
    else if (type.startsWith("scaling-factor"))
        return new ScalingFactorSettingViewModel(setting, parent);
    else if (type.startsWith("icon"))
        return new IconSettingViewModel(setting, parent);
    return new StringSettingViewModel(setting, parent);
}
