#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Domain/UserScripts/UserScripts.hpp>

using namespace MellowPlayer::Domain;

UserScripts::UserScripts(const QString& serviceName, IUserScriptFactory& userScriptFactory, ISettingsStore& settingsStore)
        : _serviceName(serviceName), _userScriptFactory(userScriptFactory), _settingsStore(settingsStore), _logger(Loggers::logger("UserScripts"))
{
    auto scriptPaths = settingsStore.value(pathsKey(), QStringList()).toStringList();
    auto scriptNames = settingsStore.value(namesKey(), QStringList()).toStringList();

    for (int i = 0; i < scriptPaths.count(); ++i)
    {
        auto path = scriptPaths.at(i);
        auto name = scriptNames.at(i);
        auto* userScript = _userScriptFactory.create();
        userScript->setName(name);
        if (userScript->load(path))
            _scripts.append(userScript);
    }
}

UserScripts::~UserScripts()
{
    qDeleteAll(_scripts);
}

int UserScripts::count() const
{
    return _scripts.count();
}

IUserScript* UserScripts::add(const QString& userScriptName, const QString& sourceScriptPath)
{
    QString sourcePath = sourceScriptPath;
#ifdef Q_OS_WIN
    sourcePath = sourcePath.replace("file:///", "");
#endif
    LOG_DEBUG(_logger, "Add user script " << userScriptName.toStdString() << " from " << sourceScriptPath.toStdString());
    auto* userScript = _userScriptFactory.create();
    userScript->setName(userScriptName);
    if (userScript->import(sourcePath))
    {
        _scripts.append(userScript);
        save(userScriptName, userScript);
        return userScript;
    }
    else
    {
        delete userScript;
        return nullptr;
    }
}

void UserScripts::save(const QString& userScriptName, const IUserScript* userScript) const
{
    auto scriptPaths = _settingsStore.value(pathsKey(), QStringList()).toStringList();
    scriptPaths.append(userScript->path());
    auto scriptNames = _settingsStore.value(namesKey(), QStringList()).toStringList();
    scriptNames.append(userScriptName);
    _settingsStore.setValue(pathsKey(), scriptPaths);
    _settingsStore.setValue(namesKey(), scriptNames);
}

void UserScripts::remove(const QString& scriptName)
{
    int index = 0;
    for (index = 0; index < _scripts.count(); ++index)
    {
        IUserScript* script = _scripts.at(index);
        if (script->name() == scriptName)
        {
            auto scriptPaths = _settingsStore.value(pathsKey(), QStringList()).toStringList();
            auto scriptNames = _settingsStore.value(namesKey(), QStringList()).toStringList();
            scriptNames.removeOne(_scripts.at(index)->name());
            scriptPaths.removeOne(_scripts.at(index)->path());
            _settingsStore.setValue(pathsKey(), scriptPaths);
            _settingsStore.setValue(namesKey(), scriptNames);
            script->removeFile();
            _scripts.removeAt(index);
            delete script;
            break;
        }
    }
}

UserScripts::const_iterator UserScripts::begin(void) const
{
    return _scripts.begin();
}

UserScripts::const_iterator UserScripts::end(void) const
{
    return _scripts.end();
}

QString UserScripts::pathsKey() const
{
    return _serviceName + "/userScriptPaths";
}

QString UserScripts::namesKey() const
{
    return _serviceName + "/userScriptNames";
}
