#include "RemoteControlViewModel.hpp"
#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>
#include <MellowPlayer/Domain/RemoteControl/IRemoteControlApplication.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

#define REMOTE_CONTROL_STATE_NOT_ENABLED "NotEnabled"
#define REMOTE_CONTROL_STATE_NOT_INSTALLED "NotInstalled"
#define REMOTE_CONTROL_STATE_INSTALLING "Installing"
#define REMOTE_CONTROL_STATE_STOPPED "Stopped"
#define REMOTE_CONTROL_STATE_RUNNING "Running"

RemoteControlStateViewModel::RemoteControlStateViewModel(const QString& name, const QString& qmlComponent) : _name(name), _qmlComponent(qmlComponent)
{
}

QString RemoteControlStateViewModel::name() const
{
    return _name;
}

QString RemoteControlStateViewModel::qmlComponent() const
{
    return _qmlComponent;
}

RemoteControlApplicationInfoViewModel::RemoteControlApplicationInfoViewModel(IRemoteControlApplication& remoteControlApplication)
        : _remoteControlApplication(remoteControlApplication)
{
    connect(&_remoteControlApplication, &IRemoteControlApplication::installationStateChanged, this, &RemoteControlApplicationInfoViewModel::versionChanged);
}

QString RemoteControlApplicationInfoViewModel::name() const
{
    return _remoteControlApplication.name();
}

QString RemoteControlApplicationInfoViewModel::homePage() const
{
    return _remoteControlApplication.homePage();
}

QString RemoteControlApplicationInfoViewModel::logo() const
{
    return _remoteControlApplication.logo();
}

QString RemoteControlApplicationInfoViewModel::url() const
{
    return _remoteControlApplication.url();
}

QString RemoteControlApplicationInfoViewModel::minimumRequiredVersion() const
{
    return _remoteControlApplication.minimumRequiredVersion();
}

QString RemoteControlApplicationInfoViewModel::version() const
{
    return _remoteControlApplication.version();
}

RemoteControlViewModel::RemoteControlViewModel(IRemoteControl& remoteControl)
        : QmlSingleton("RemoteControl", this),
          _remoteControl(remoteControl),
          _remoteControlApplication(remoteControl.application()),
          _appInfo(remoteControl.application())
{
    addState(new RemoteControlStateViewModel{REMOTE_CONTROL_STATE_NOT_ENABLED,
                                             "qrc:/MellowPlayer/imports/MellowPlayer/SettingsPages/RemoteControl/RemoteControlState_NotEnabled.qml"});
    addState(new RemoteControlStateViewModel{REMOTE_CONTROL_STATE_NOT_INSTALLED,
                                             "qrc:/MellowPlayer/imports/MellowPlayer/SettingsPages/RemoteControl/RemoteControlState_NotInstalled.qml"});
    addState(new RemoteControlStateViewModel{REMOTE_CONTROL_STATE_INSTALLING,
                                             "qrc:/MellowPlayer/imports/MellowPlayer/SettingsPages/RemoteControl/RemoteControlState_Installing.qml"});
    addState(new RemoteControlStateViewModel{REMOTE_CONTROL_STATE_STOPPED,
                                             "qrc:/MellowPlayer/imports/MellowPlayer/SettingsPages/RemoteControl/RemoteControlState_Stopped.qml"});
    addState(new RemoteControlStateViewModel{REMOTE_CONTROL_STATE_RUNNING,
                                             "qrc:/MellowPlayer/imports/MellowPlayer/SettingsPages/RemoteControl/RemoteControlState_Running.qml"});

    connect(&_remoteControl, &IRemoteControl::enabledChanged, this, &RemoteControlViewModel::currentStateIndexChanged);
    connect(&_remoteControl, &IRemoteControl::autoStartEnabledChanged, this, &RemoteControlViewModel::autoStartEnabledChanged);
    connect(&_remoteControlApplication, &IRemoteControlApplication::installationStateChanged, this, &RemoteControlViewModel::currentStateIndexChanged);
    connect(&_remoteControlApplication, &IRemoteControlApplication::installingChanged, this, &RemoteControlViewModel::currentStateIndexChanged);
    connect(&_remoteControlApplication, &IRemoteControlApplication::runningChanged, this, &RemoteControlViewModel::currentStateIndexChanged);
}

void RemoteControlViewModel::addState(RemoteControlStateViewModel* state)
{
    _stateByName[state->name()] = state;
    _states.append(state);
}

QQmlObjectListModel<RemoteControlStateViewModel>* RemoteControlViewModel::states()
{
    return &_states;
}

RemoteControlApplicationInfoViewModel* RemoteControlViewModel::appInfo()
{
    return &_appInfo;
}

int RemoteControlViewModel::currentStateIndex() const
{
    auto* currentState = _stateByName[currentStateName()];
    return currentState != nullptr ? _states.indexOf(currentState) : -1;
}

QString RemoteControlViewModel::currentStateName() const
{
    if (!_remoteControl.isEnabled())
        return REMOTE_CONTROL_STATE_NOT_ENABLED;

    if (_remoteControlApplication.isInstalling())
        return REMOTE_CONTROL_STATE_INSTALLING;

    if (!_remoteControlApplication.isInstalled())
        return REMOTE_CONTROL_STATE_NOT_INSTALLED;

    return _remoteControlApplication.isRunning() ? REMOTE_CONTROL_STATE_RUNNING : REMOTE_CONTROL_STATE_STOPPED;
}

void RemoteControlViewModel::activate()
{
    _remoteControl.activate();
    _remoteControlApplication.checkInstallation();
}

void RemoteControlViewModel::deactivate()
{
    _remoteControl.deactivate();
}

void RemoteControlViewModel::install()
{
    _remoteControlApplication.install([=](bool success, const QString& errorMessage) {
        if (!success)
            emit error("Installation failed", errorMessage);
    });
}

void RemoteControlViewModel::start()
{
    _remoteControlApplication.start();
}

void RemoteControlViewModel::stop()
{
    _remoteControlApplication.stop();
}

bool RemoteControlViewModel::isAutoStartEnabled() const
{
    return _remoteControl.isAutoStartEnabled();
}

void RemoteControlViewModel::setAutoStartEnabled(bool value)
{
    _remoteControl.setAutoStartEnabled(value);
}
