#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

ColorSettingViewModel::ColorSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}


QString ColorSettingViewModel::qmlComponent()
{
    return "Delegates/ColorSettingDelegate.qml";
}
