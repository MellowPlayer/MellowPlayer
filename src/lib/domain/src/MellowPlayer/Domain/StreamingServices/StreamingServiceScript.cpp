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

QString StreamingServiceScript::constants() const
{
    return "mellowplayer = {\n"
           "    PlaybackStatus: {\n"
           "        STOPPED: 0,\n"
           "        PLAYING: 1,\n"
           "        PAUSED: 2,\n"
           "        BUFFERING: 3\n"
           "    }\n"
           "};\n"
           "function getHashCode(s) {\n"
           "    return s.split(\"\").reduce(function(a, b) {\n"
           "        a = ((a << 5) - a) + b.charCodeAt(0);\n"
           "        return a & a\n"
           "    }, 0);\n"
           "}\n"
           "function toSeconds(string) {\n"
           "    try {\n"
           "        var dtimes = string.split(\":\");\n"
           "\n"
           "        if (dtimes.length === 3) {\n"
           "            var dhours = dtimes[0];\n"
           "            var dminutes = dtimes[1];\n"
           "            var dseconds = dtimes[2];\n"
           "            var duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60) + (parseInt(dhours, 10) * 60 * 60);\n"
           "        }\n"
           "        else {\n"
           "            var dminutes = dtimes[0];\n"
           "            var dseconds = dtimes[1];\n"
           "            var duration = parseInt(dseconds, 10) + (parseInt(dminutes, 10) * 60);\n"
           "        }\n"
           "\n"
           "    } catch (e) {\n"
           "        var duration = 0;\n"
           "    }\n"
           "\n"
           "    return duration\n"
           "}";
}
