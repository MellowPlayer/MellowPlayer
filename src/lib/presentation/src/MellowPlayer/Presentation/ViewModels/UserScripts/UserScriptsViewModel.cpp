#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>
#include <QFileInfo>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserScriptsViewModel::UserScriptsViewModel(const QString& serviceName, IUserScriptFactory& userScriptFactory, ISettingsStore& settingsStore, QObject* parent)
        : QObject(parent), _userScripts(serviceName, userScriptFactory, settingsStore)
{
    for (auto* userScriptModel : _userScripts)
    {
        create(userScriptModel);
    }
}

QQmlObjectListModelBase* UserScriptsViewModel::model()
{
    return &_model;
}

bool UserScriptsViewModel::isValidName(const QString& name) const
{
    QStringList names;

    for (auto* userScriptModel : _userScripts)
        names.append(userScriptModel->name());

    return !names.contains(name);
}

bool UserScriptsViewModel::add(const QString& name, const QString& sourcePath)
{
    bool hadUserScripts = hasScripts();
    IUserScript* userScriptModel = _userScripts.add(name, sourcePath);
    if (userScriptModel != nullptr)
    {
        create(userScriptModel);
        if (hadUserScripts != hasScripts())
            emit hasScriptsChanged();

        return true;
    }

    return false;
}

void UserScriptsViewModel::remove(const QString& name)
{
    bool hadUserScripts = hasScripts();
    for (int i = 0; i < _model.count(); ++i)
    {
        if (_model.at(i)->name() == name)
        {
            _model.remove(i);
        }
    }
    _userScripts.remove(name);

    if (hadUserScripts != hasScripts())
        emit hasScriptsChanged();
}

void UserScriptsViewModel::create(IUserScript* userScriptModel)
{
    auto* userScriptViewModel = new UserScriptViewModel(*userScriptModel, this);
    _model.append(userScriptViewModel);
}

bool UserScriptsViewModel::hasScripts() const
{
    return _userScripts.count() != 0;
}

QString UserScriptsViewModel::generateUniqueName(const QString& path) const
{
    QFileInfo fileInfo(path);
    QString baseName = fileInfo.baseName();
    QString name = baseName;

    int i = 1;
    while (!isValidName(name))
    {
        ++i;
        name = baseName + QString::number(i);
    }

    return name;
}
