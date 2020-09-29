#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

BoolSettingViewModel::BoolSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString BoolSettingViewModel::qmlComponent()
{
    return "Delegates/BoolSettingDelegate.qml";
}
