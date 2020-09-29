#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/IconSettingViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

IconSettingViewModel::IconSettingViewModel(Setting &setting, QObject *parent) : SettingViewModel(setting, parent)
{
}

QString IconSettingViewModel::qmlComponent()
{
    return "Delegates/IconSettingDelegate.qml";
}
