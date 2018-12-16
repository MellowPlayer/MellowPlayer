#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ScalingFactorSettingViewModel.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ScalingFactorSettingViewModel::ScalingFactorSettingViewModel(Setting &setting, QObject *parent)
        : SettingViewModel(setting, parent)
{

}

int ScalingFactorSettingViewModel::getValue() const
{
    int value = setting_.value().toInt();
    return value;
}

void ScalingFactorSettingViewModel::setValue(int value)
{
    setting_.setValue(value);
}

QString ScalingFactorSettingViewModel::qmlComponent()
{
    return "Delegates/IntSettingDelegate.qml";
}

void ScalingFactorSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

int ScalingFactorSettingViewModel::minValue() const
{
    return 100;
}

int ScalingFactorSettingViewModel::maxValue() const
{
    return 300;
}

int ScalingFactorSettingViewModel::step() const
{
    return 10;
}

QString ScalingFactorSettingViewModel::suffix() const
{
    return "%";
}

