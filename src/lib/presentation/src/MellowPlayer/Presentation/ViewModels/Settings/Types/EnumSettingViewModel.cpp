#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

EnumSettingViewModel::EnumSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString EnumSettingViewModel::qmlComponent()
{
    return "Delegates/EnumSettingDelegate.qml";
}

QStringList EnumSettingViewModel::values() const
{
    QString list = _setting.type();
    list = list.replace("enum[", "").replace("]", "").replace("'", "").replace("\"", "").replace(" ", "");
    return list.split(",");
}
