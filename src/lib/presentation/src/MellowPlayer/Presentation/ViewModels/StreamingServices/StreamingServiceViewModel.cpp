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
#include <QUrlQuery>
#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDesktopServices>

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
                                                     std::unique_ptr<IHttpClient> httpClient,
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
          _logger(Loggers::logger("StreamingServiceViewModel-" + name().toStdString())),
          _httpClient(std::move(httpClient))
{
    connect(&_streamingService, &StreamingService::scriptChanged, this, &StreamingServiceViewModel::sourceCodeChanged);
    Q_ASSERT(networkProxy_ != nullptr);

    LOG_DEBUG(_logger, "sort order: " << sortIndex());
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

int StreamingServiceViewModel::sortIndex() const
{
    return _settingsStore.value(sortIndexSettingKey(), "-1").toInt();
}

void StreamingServiceViewModel::setSortIndex(int newOrder)
{
    if (newOrder != sortIndex())
    {
        _settingsStore.setValue(sortIndexSettingKey(), newOrder);
        LOG_DEBUG(_logger, "sort order changed: " << sortIndex());
        emit sortIndexChanged();
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

QString StreamingServiceViewModel::sortIndexSettingKey() const
{
    return _streamingService.name() + "/sortIndex";
}

QString StreamingServiceViewModel::favoriteSettingKey() const
{
    return _streamingService.name() + "/favorite";
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
    auto sourceCode = _streamingService.script()->code();
    if (_streamingService.settings() != nullptr)
        sourceCode += QString("var pluginSettings = JSON.parse('%1')\n").arg(_streamingService.settings()->toJavascriptObject());
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

void StreamingServiceViewModel::checkForKnownIssues()
{
    auto envVar = qgetenv("MELLOWPLAYER_CHECK_PLUGIN_KNOWN_ISSUES");
    if (envVar != "0")
    {
        auto url = QUrl("https://gitlab.com/api/v4/projects/9602590/issues");
        QUrlQuery query;
        query.addQueryItem("state", "opened");
        query.addQueryItem("labels", "broken integration plugin");
        query.addQueryItem("search", name());
        query.addQueryItem("in", "title");
        url.setQuery(query);

        _httpClient->get(url, [=](const QByteArray& data) {
            auto jsonDocument = QJsonDocument::fromJson(data);
            auto issues = jsonDocument.array();
            if (issues.count() == 1)
            {
                auto issue = issues.first().toObject();
                _issueLink = issue["web_url"].toString();
                emit hasKnownIssuesChanged();
                setBroken(true);
                LOG_WARN(_logger, "Known issue found: " << _issueLink);
            }
        });
    }
}

bool StreamingServiceViewModel::isBroken() const
{
    return _isBroken;
}

void StreamingServiceViewModel::setBroken(bool value)
{
    if (_isBroken != value)
    {
        _isBroken = value;
        emit brokenChanged();

        if (_isBroken)
            LOG_WARN(_logger, name() << " integration plugin is broken");
    }
}

bool StreamingServiceViewModel::hasKnownIssues() const
{
    return !_issueLink.isEmpty();
}

void StreamingServiceViewModel::openKnownIssue()
{
    QDesktopServices::openUrl(_issueLink);
}

bool StreamingServiceViewModel::isFavorite() const
{
    return _settingsStore.value(favoriteSettingKey(), "false").toBool();
}

void StreamingServiceViewModel::setFavorite(bool value)
{
    if (value != isFavorite())
    {
        _settingsStore.setValue(favoriteSettingKey(), value);
        LOG_DEBUG(_logger, "favorite changed: " << isFavorite());
        emit favoriteChanged();
    }
}
