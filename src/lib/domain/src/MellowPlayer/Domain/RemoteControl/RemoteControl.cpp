#include "RemoteControl.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/RemoteControl/IApplicationStatusFile.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>

using namespace MellowPlayer::Domain;

RemoteControl::RemoteControl(IApplicationStatusFile& applicationStatusFile, Settings& settings, IRemoteControlApplication& remoteControlApplication)
        : _logger(Loggers::logger("RemoteControl")),
          _applicationStatusFile(applicationStatusFile),
          _settings(settings),
          _remoteControlApplication(remoteControlApplication)
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
        value ? activate() : deactivate();
    }
}

void RemoteControl::activate()
{
    LOG_DEBUG(_logger, "Activating remote control");
    _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_ENABLED).setValue(true);
    _applicationStatusFile.create();
    emit enabledChanged();
}

void RemoteControl::deactivate()
{
    LOG_DEBUG(_logger, "Deactivating remote control");
    _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_ENABLED).setValue(false);
    _applicationStatusFile.remove();
    emit enabledChanged();
}

bool RemoteControl::isAutoStartEnabled() const
{
    return _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_AUTO_START).value().toBool();
}

void RemoteControl::setAutoStartEnabled(bool value)
{
    if (value != isAutoStartEnabled())
    {
        LOG_DEBUG(_logger, "Automatic startup: " << value);
        _settings.get(SettingKey::PRIVATE_REMOTE_CONTROL_AUTO_START).setValue(value);
        emit autoStartEnabledChanged();
    }
}

IRemoteControlApplication& RemoteControl::application() const
{
    return _remoteControlApplication;
}
