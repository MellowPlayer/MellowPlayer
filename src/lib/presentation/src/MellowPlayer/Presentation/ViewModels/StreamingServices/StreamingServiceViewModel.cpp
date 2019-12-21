#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <qfile.h>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

#define DEFAULT_ZOOM_FACTOR 7

StreamingServiceViewModel::StreamingServiceViewModel(StreamingService& streamingService,
                                                     ISettingsStore& settingsStore,
                                                     IUserScriptFactory& factory,
                                                     Players& players,
                                                     INetworkProxies& networkProxies,
                                                     ThemeViewModel& themeViewModel,
                                                     QObject* parent)
        : QObject(parent),
          networkProxy_(networkProxies.get(streamingService.name())),
          _streamingService(streamingService),
          _settingsStore(settingsStore),
          _player(players.get(streamingService.name())),
          _userScriptsViewModel(streamingService.name(), factory, settingsStore, this),
          _zoomFactor(_settingsStore.value(zoomFactorSettingsKey(), 7).toInt()),
          _isActive(false),
          _previewImageUrl("qrc:/MellowPlayer/Presentation/images/home-background.png"),
          _settingsCategoryViewModel(themeViewModel, streamingService.settings()),
          _logger(Loggers::logger("StreamingServiceViewModel-" + name().toStdString()))
{
    connect(&_streamingService, &StreamingService::scriptChanged, this, &StreamingServiceViewModel::sourceCodeChanged);
    Q_ASSERT(networkProxy_ != nullptr);

    if (isEnabled())
        LOG_DEBUG(_logger, "sort order: " << sortOrder());
}

QString StreamingServiceViewModel::logo() const
{
    return _streamingService.logo();
}

QString StreamingServiceViewModel::name() const
{
    return _streamingService.name();
}

Player* StreamingServiceViewModel::player()
{
    return _player.get();
}

QString StreamingServiceViewModel::url() const
{
    QString customUrl = _settingsStore.value(customUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? _streamingService.url() : customUrl;
}

QString StreamingServiceViewModel::version() const
{
    return _streamingService.version();
}

QString StreamingServiceViewModel::authorName() const
{
    return _streamingService.author();
}

QString StreamingServiceViewModel::authorWebsite() const
{
    return _streamingService.authorWebsite();
}

bool StreamingServiceViewModel::operator==(const StreamingServiceViewModel& rhs) const
{
    return _streamingService == rhs._streamingService;
}

bool StreamingServiceViewModel::operator!=(const StreamingServiceViewModel& rhs) const
{
    return !operator==(rhs);
}

StreamingService* StreamingServiceViewModel::streamingService() const
{
    return &_streamingService;
}

int StreamingServiceViewModel::sortOrder() const
{
    return _settingsStore.value(sortOrderSettingsKey(), "-1").toInt();
}

void StreamingServiceViewModel::setSortOrder(int newOrder)
{
    if (newOrder != sortOrder())
    {
        _settingsStore.setValue(sortOrderSettingsKey(), newOrder);
        LOG_DEBUG(_logger, "sort order changed: " << sortOrder());
        emit sortOrderChanged();
    }
}

bool StreamingServiceViewModel::isEnabled() const
{
    return _settingsStore.value(isEnabledSettingsKey(), "true").toBool();
}

void StreamingServiceViewModel::setEnabled(bool enabled)
{
    if (enabled != isEnabled())
    {
        _settingsStore.setValue(isEnabledSettingsKey(), enabled);
        LOG_DEBUG(_logger, "enabled changed: " << sortOrder());
        emit isEnabledChanged();

        if (!enabled)
        {
            _player->suspend();
            setSortOrder(255);
        }
    }
}

void StreamingServiceViewModel::setUrl(const QString& newUrl)
{
    if (newUrl != url())
    {
        _settingsStore.setValue(customUrlSettingsKey(), newUrl);
        emit urlChanged(newUrl);
    }
}

void StreamingServiceViewModel::setActive(bool isActive)
{
    if (_isActive == isActive)
        return;

    _isActive = isActive;
    if (!_isActive)
        setPreviewImageUrl("qrc:/MellowPlayer/Presentation/images/home-background.png");
    emit isActiveChanged();
}

void StreamingServiceViewModel::setPreviewImageUrl(QString previewImageUrl)
{
    if (_previewImageUrl == previewImageUrl)
        return;

    _previewImageUrl = previewImageUrl;
    emit previewImageUrlChanged();
}

QString StreamingServiceViewModel::customUrlSettingsKey() const
{
    return _streamingService.name() + "/url";
}

QString StreamingServiceViewModel::sortOrderSettingsKey() const
{
    return _streamingService.name() + "/sortOrder";
}

QString StreamingServiceViewModel::isEnabledSettingsKey() const
{
    return _streamingService.name() + "/isEnabled";
}

QObject* StreamingServiceViewModel::userScripts()
{
    return &_userScriptsViewModel;
}

int StreamingServiceViewModel::zoomFactor() const
{
    return _zoomFactor;
}

void StreamingServiceViewModel::setZoomFactor(int zoomFactor)
{
    if (_zoomFactor != zoomFactor)
    {
        _zoomFactor = zoomFactor;
        _settingsStore.setValue(zoomFactorSettingsKey(), zoomFactor);
        emit zoomFactorChanged();
    }
}

QString StreamingServiceViewModel::zoomFactorSettingsKey() const
{
    return _streamingService.name() + "/zoomFactor";
}

bool StreamingServiceViewModel::notificationsEnabled() const
{
    return _settingsStore.value(notificationsEnabledSettingsKey(), true).toBool();
}

void StreamingServiceViewModel::setNotificationsEnabled(bool value)
{
    if (value != notificationsEnabled())
    {
        _settingsStore.setValue(notificationsEnabledSettingsKey(), value);
        emit notificationsEnabledChanged();
    }
}

bool StreamingServiceViewModel::isActive() const
{
    return _isActive;
}

QString StreamingServiceViewModel::previewImageUrl() const
{
    return _previewImageUrl;
}

QString StreamingServiceViewModel::notificationsEnabledSettingsKey() const
{
    return _streamingService.name() + "/notificationsEnabled";
}

QString StreamingServiceViewModel::sourceCode() const
{
    auto sourceCode = _streamingService.script()->constants() + "\n" + _streamingService.script()->code() + "\n";
    if (_streamingService.settings() != nullptr)
        sourceCode += QString("var pluginSettings = JSON.parse(_'%1')\n").arg(_streamingService.settings()->toJavascriptObject());
    return sourceCode;
}

SettingsCategoryViewModel* StreamingServiceViewModel::settings()
{
    return &_settingsCategoryViewModel;
}

QString StreamingServiceViewModel::getPreviewImageUrlForSave()
{
    ++_previewCount;
    if (_previewCount > 10)
        _previewCount = 1;

    auto cacheDir = QDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    auto dir = QFileInfo(cacheDir, "Preview");
    auto dirPath = dir.absoluteFilePath();
    QDir().mkpath(dirPath);
    auto filePath = QFileInfo(dirPath, QString("%1-%2.jpg").arg(name()).arg(_previewCount)).absoluteFilePath();
    return filePath;
}
