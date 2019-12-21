#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

StringSettingViewModel::StringSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString StringSettingViewModel::getValue() const
{
    return _setting.value().toString();
}

void StringSettingViewModel::setValue(QString value)
{
    _setting.setValue(value);
}

void StringSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString StringSettingViewModel::qmlComponent()
{
    return "Delegates/StringSettingDelegate.qml";
}
