#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserScriptViewModel::UserScriptViewModel(IUserScript& model, QObject* parent) : QObject(parent), _model(model)
{
}

QString UserScriptViewModel::name() const
{
    return _model.name();
}

void UserScriptViewModel::setName(const QString& name)
{
    Q_UNUSED(name);
    if (name != _model.name())
    {
        _model.setName(name);
        emit nameChanged();
    }
}

QString UserScriptViewModel::code() const
{
    return _model.code();
}

QString UserScriptViewModel::path() const
{
    return _model.path();
}

IUserScript& UserScriptViewModel::model()
{
    return _model;
}
