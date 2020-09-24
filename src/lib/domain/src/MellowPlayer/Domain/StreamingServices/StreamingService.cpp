#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

StreamingService::StreamingService(const StreamingServiceMetadata& metadata, const Theme& theme, const std::shared_ptr<SettingsCategory>& settings)
        : _metadata(metadata), _theme(theme), _settings(settings), _script(make_unique<StreamingServiceScript>(metadata.script, metadata.scriptPath))
{
}

StreamingService::~StreamingService() = default;

const QString& StreamingService::author() const
{
    return _metadata.author;
}

const QString& StreamingService::authorWebsite() const
{
    return _metadata.authorWebsite;
}

QString StreamingService::logo() const
{
    if (_metadata.logoPath.isEmpty())
        return "";
#ifdef Q_OS_WIN
    return "file:" + _metadata.logoPath;
#else
    return "file://" + _metadata.logoPath;
#endif
}

const QString& StreamingService::name() const
{
    return _metadata.name;
}

QString StreamingService::url() const
{
    return _metadata.url;
}

const QString& StreamingService::version() const
{
    return _metadata.version;
}

bool StreamingService::isValid() const
{
    return _metadata.isValid() && _script->isValid();
}

StreamingServiceScript* StreamingService::script() const
{
    return _script.get();
}

const Theme& StreamingService::theme() const
{
    return _theme;
}

bool StreamingService::operator==(const StreamingService& rhs) const
{
    return name() == rhs.name();
}

bool StreamingService::operator!=(const StreamingService& rhs) const
{
    return !operator==(rhs);
}

SettingsCategory* StreamingService::settings() const
{
    return _settings.get();
}

void StreamingService::updateTheme(Theme& newTheme)
{
    _theme = newTheme;
    emit themeChanged();
}

void StreamingService::updateScript(const QString& scriptCode)
{
    _script->setCode(scriptCode);
    emit scriptChanged();
}

QString StreamingService::pluginDirectory() const
{
    return _metadata.pluginDirectory;
}
