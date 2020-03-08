#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>

using namespace MellowPlayer::Domain;

StreamingServiceScript::StreamingServiceScript(const QString& code, const QString& path) : QObject(), _code(code), _path(path)
{
}

bool StreamingServiceScript::isValid() const
{
    return _code.contains("function update") && _code.contains("function play") &&
           (_code.contains("function pause") && _code.contains("function goNext") && _code.contains("function goPrevious") &&
            _code.contains("function setVolume") && _code.contains("function addToFavorites")) &&
           _code.contains("function removeFromFavorites") && _code.contains("function seekToPosition");
}

QString StreamingServiceScript::code() const
{
    return _code;
}

void StreamingServiceScript::setCode(const QString& value)
{
    if (_code == value)
        return;
    _code = value;
    emit codeChanged(value);
}

const QString& StreamingServiceScript::path() const
{
    return _path;
}
