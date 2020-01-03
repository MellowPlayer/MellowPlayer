#include "RemoteControl.hpp"
#include <MellowPlayer/Domain/RemoteControl/IApplicationStatusFile.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Domain;

RemoteControl::RemoteControl(IApplicationStatusFile& applicationStatusFile, Settings& settings)
        : _applicationStatusFile(applicationStatusFile), _settings(settings)
{
}

bool RemoteControl::isEnabled() const
{
    return _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_ENABLED).value().toBool();
}

void RemoteControl::setEnabled(bool value)
{
    if (isEnabled() != value)
    {
        if (value)
            activate();
        else
            deactivate();
    }
}

void RemoteControl::activate()
{
    _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_ENABLED).setValue(true);
    _applicationStatusFile.create();
}

void RemoteControl::deactivate()
{
    _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_ENABLED).setValue(false);
    _applicationStatusFile.remove();
}

bool RemoteControl::isAutoStartEnabled() const
{
    return _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_AUTO_START).value().toBool();
}

void RemoteControl::setAutoStartEnabled(bool value)
{
    _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_AUTO_START).setValue(value);
}
