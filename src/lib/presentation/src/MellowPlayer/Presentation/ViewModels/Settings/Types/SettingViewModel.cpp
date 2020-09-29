#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingViewModel::SettingViewModel(Setting& setting, QObject* parent) : QObject(parent), _setting(setting)
{
    connect(&setting, &Setting::valueChanged, this, &SettingViewModel::valueChanged);
    connect(&setting, &Setting::isEnabledChanged, this, &SettingViewModel::onEnabledChanged);
}

QString SettingViewModel::name() const
{
    return _setting.name();
}

QString SettingViewModel::toolTip() const
{
    return _setting.toolTip();
}

QString SettingViewModel::type() const
{
    return _setting.type();
}

bool SettingViewModel::enabled() const
{
    return _setting.isEnabled();
}

void SettingViewModel::onEnabledChanged()
{
    emit enabledChanged();
}

QVariant SettingViewModel::value() const
{
    return _setting.value();
}

void SettingViewModel::setValue(const QVariant& value)
{
    _setting.setValue(value);
}