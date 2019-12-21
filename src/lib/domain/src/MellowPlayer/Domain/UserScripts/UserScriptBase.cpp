#include <MellowPlayer/Domain/UserScripts/UserScriptBase.hpp>

using namespace MellowPlayer::Domain;

QString UserScriptBase::path() const
{
    return _path;
}

QString UserScriptBase::code() const
{
    return _code;
}

QString UserScriptBase::name() const
{
    return _name;
}

void UserScriptBase::setName(const QString& name)
{
    _name = name;
}
