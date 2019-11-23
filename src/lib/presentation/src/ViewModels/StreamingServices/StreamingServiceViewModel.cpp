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
                                                     QObject* parent) :
        QObject(parent),
        networkProxy_(networkProxies.get(streamingService.name())),
        streamingService_(streamingService), 
        settingsStore_(settingsStore),
        player_(players.get(streamingService.name())),
        userScriptsViewModel_(streamingService.name(), factory, settingsStore, this),
        zoomFactor_(settingsStore_.value(zoomFactorSettingsKey(), 7).toInt()),
        isActive_(false),
        previewImageUrl_("qrc:/MellowPlayer/Presentation/images/home-background.png"),
        _settingsCategoryViewModel(themeViewModel, streamingService.settings()),
        logger_(Loggers::logger("StreamingServiceViewModel-" + name().toStdString()))
{
    connect(&streamingService_, &StreamingService::scriptChanged, this, &StreamingServiceViewModel::sourceCodeChanged);
    Q_ASSERT(networkProxy_ != nullptr);

    if (isEnabled())
        LOG_DEBUG(logger_, "sort order: " << sortOrder());
}

QString StreamingServiceViewModel::logo() const
{
    return streamingService_.logo();
}

QString StreamingServiceViewModel::name() const
{
    return streamingService_.name();
}

Player* StreamingServiceViewModel::player()
{
    return player_.get();
}

QString StreamingServiceViewModel::url() const
{
    QString customUrl = settingsStore_.value(customUrlSettingsKey(), "").toString();
    return customUrl.isEmpty() ? streamingService_.url() : customUrl;
}

QString StreamingServiceViewModel::version() const
{
    return streamingService_.version();
}

QString StreamingServiceViewModel::authorName() const
{
    return streamingService_.author();
}

QString StreamingServiceViewModel::authorWebsite() const
{
    return streamingService_.authorWebsite();
}

bool StreamingServiceViewModel::operator==(const StreamingServiceViewModel& rhs) const
{
    return streamingService_ == rhs.streamingService_;
}

bool StreamingServiceViewModel::operator!=(const StreamingServiceViewModel& rhs) const
{
    return !operator==(rhs);
}

StreamingService* StreamingServiceViewModel::streamingService() const
{
    return &streamingService_;
}

int StreamingServiceViewModel::sortOrder() const
{
    return settingsStore_.value(sortOrderSettingsKey(), "-1").toInt();
}

void StreamingServiceViewModel::setSortOrder(int newOrder)
{
    if (newOrder != sortOrder()) {
        settingsStore_.setValue(sortOrderSettingsKey(), newOrder);
        LOG_DEBUG(logger_, "sort order changed: " << sortOrder());
        emit sortOrderChanged();
    }
}

bool StreamingServiceViewModel::isEnabled() const
{
    return settingsStore_.value(isEnabledSettingsKey(), "true").toBool();
}

void StreamingServiceViewModel::setEnabled(bool enabled)
{
    if (enabled != isEnabled()) {
        settingsStore_.setValue(isEnabledSettingsKey(), enabled);
        LOG_DEBUG(logger_, "enabled changed: " << sortOrder());
        emit isEnabledChanged();

        if (!enabled) {
            player_->suspend();
            setSortOrder(255);
        }
    }
}

void StreamingServiceViewModel::setUrl(const QString& newUrl)
{
    if (newUrl != url()) {
        settingsStore_.setValue(customUrlSettingsKey(), newUrl);
        emit urlChanged(newUrl);
    }
}

void StreamingServiceViewModel::setActive(bool isActive)
{
    if (isActive_ == isActive)
        return;

    isActive_ = isActive;
    if (!isActive_)
        setPreviewImageUrl("qrc:/MellowPlayer/Presentation/images/home-background.png");
    emit isActiveChanged();
}

void StreamingServiceViewModel::setPreviewImageUrl(QString previewImageUrl)
{
    if (previewImageUrl_ == previewImageUrl)
        return;

    previewImageUrl_ = previewImageUrl;
    emit previewImageUrlChanged();
}

QString StreamingServiceViewModel::customUrlSettingsKey() const
{
    return streamingService_.name() + "/url";
}

QString StreamingServiceViewModel::sortOrderSettingsKey() const
{
    return streamingService_.name() + "/sortOrder";
}

QString StreamingServiceViewModel::isEnabledSettingsKey() const
{
    return streamingService_.name() + "/isEnabled";
}

QObject* StreamingServiceViewModel::userScripts()
{
    return &userScriptsViewModel_;
}

int StreamingServiceViewModel::zoomFactor() const {
    return zoomFactor_;
}

void StreamingServiceViewModel::setZoomFactor(int zoomFactor) {
    if (zoomFactor_ != zoomFactor) {
        zoomFactor_ = zoomFactor;
        settingsStore_.setValue(zoomFactorSettingsKey(), zoomFactor);
        emit zoomFactorChanged();
    }

}

QString StreamingServiceViewModel::zoomFactorSettingsKey() const {
    return streamingService_.name() + "/zoomFactor";
}

bool StreamingServiceViewModel::notificationsEnabled() const
{
    return settingsStore_.value(notificationsEnabledSettingsKey(), true).toBool();
}

void StreamingServiceViewModel::setNotificationsEnabled(bool value)
{
    if (value != notificationsEnabled())
    {
        settingsStore_.setValue(notificationsEnabledSettingsKey(), value);
        emit notificationsEnabledChanged();
    }
}

bool StreamingServiceViewModel::isActive() const
{
    return isActive_;
}

QString StreamingServiceViewModel::previewImageUrl() const
{
    return previewImageUrl_;
}

QString StreamingServiceViewModel::notificationsEnabledSettingsKey() const
{
    return streamingService_.name() + "/notificationsEnabled";
}

QString StreamingServiceViewModel::sourceCode() const
{
    auto sourceCode = streamingService_.script()->constants() + "\n" + streamingService_.script()->code() + "\n";
    if (streamingService_.settings() != nullptr)
        sourceCode += QString("var pluginSettings = JSON.parse('%1')\n").arg(streamingService_.settings()->toJavascriptObject());
    return sourceCode;
}

SettingsCategoryViewModel *StreamingServiceViewModel::settings()
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
