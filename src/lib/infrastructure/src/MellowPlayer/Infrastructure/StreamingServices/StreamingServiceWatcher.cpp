#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <QtCore/QDir>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

StreamingServiceWatcher::StreamingServiceWatcher() : _logger(Loggers::logger("StreamingServiceWatcher"))
{
    connect(&_fileSystemWatcher, &QFileSystemWatcher::fileChanged, this, &StreamingServiceWatcher::onFileChanged);
}

void StreamingServiceWatcher::watch(StreamingService& serviceToWatch)
{
    const QString pluginDirectory = serviceToWatch.pluginDirectory();
    const QString themePath = QDir::cleanPath(pluginDirectory + "/" + "theme.json");
    const QString scriptPath = QDir::cleanPath(pluginDirectory + "/" + "integration.js");

    _pluginInfo.insert(pluginDirectory, new PluginInfo(serviceToWatch, scriptPath, themePath, this));

    watchPath(themePath);
    watchPath(scriptPath);
}

void StreamingServiceWatcher::watchPath(const QString& path)
{
    LOG_TRACE(_logger, "Watching path: " + path);
    _fileSystemWatcher.addPath(path);
}

void StreamingServiceWatcher::onFileChanged(const QString& path)
{
    LOG_DEBUG(_logger, "Plugin file changed: " + path);
    QFileInfo fileInfo(path);
    const QString pluginDir = fileInfo.dir().absolutePath();
    const QString name = fileInfo.baseName();
    StreamingService& service = _pluginInfo[pluginDir]->_service;

    if (name == "integration")
    {
        service.updateScript(StreamingServiceLoader::readFileContent(path));
    }
    else
    {
        Theme theme = StreamingServiceLoader::readTheme(path);
        service.updateTheme(theme);
    }

    _fileSystemWatcher.removePath(path);
    _fileSystemWatcher.addPath(path);
}

StreamingServiceWatcher::PluginInfo::PluginInfo(StreamingService& service, QString scriptPath, QString themePath, QObject* parent)
        : QObject(parent), _service(service), _scriptPath(scriptPath), _themePath(themePath)
{
}
