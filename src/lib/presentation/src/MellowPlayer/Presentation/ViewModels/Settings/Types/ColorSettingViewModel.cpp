#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

ColorSettingViewModel::ColorSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QColor ColorSettingViewModel::getValue() const
{
    return QColor(_setting.value().toString());
}

void ColorSettingViewModel::setValue(QColor value)
{
    _setting.setValue(value.name());
}

void ColorSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString ColorSettingViewModel::qmlComponent()
{
    return "Delegates/ColorSettingDelegate.qml";
}
