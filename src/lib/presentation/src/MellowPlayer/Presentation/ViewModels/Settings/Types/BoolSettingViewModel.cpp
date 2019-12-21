#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

BoolSettingViewModel::BoolSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

bool BoolSettingViewModel::getValue() const
{
    return _setting.value().toBool();
}

void BoolSettingViewModel::setValue(bool value)
{
    _setting.setValue(value);
}

void BoolSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString BoolSettingViewModel::qmlComponent()
{
    return "Delegates/BoolSettingDelegate.qml";
}
