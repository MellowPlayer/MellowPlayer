#include "PlayerNotifications.hpp"
#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

PlayerNotifications::PlayerNotifications(IPlayer& player,
                                                         ILocalAlbumArt& localAlbumArtService,
                                                         INotificationPresenter& presenter,
                                                         StreamingServices& streamingServices,
                                                         Settings& settings)
        : _logger(Loggers::logger("PlayerNotifications")),
          _player(player),
          _localAlbumArt(localAlbumArtService),
          _presenter(presenter),
          _streamingServices(streamingServices),
          _settings(settings)
{
}

bool PlayerNotifications::display(const Notification& notification)
{
    if (!isNotificationTypeEnabled(notification.type) || _previousNotif == notification)
    {
        LOG_DEBUG(_logger, "notification disabled: " + notification.toString());
        return false;
    }
    LOG_INFO(_logger, notification.toString());
    _presenter.display(notification);
    return true;
}

void PlayerNotifications::onCurrentSongChanged(Song* song)
{
    LOG_TRACE(_logger, "onCurrentSongChanged");
    showSongNotification(song, _localAlbumArt.url());
}

void PlayerNotifications::onPlaybackStatusChanged()
{
    LOG_TRACE(_logger, "onPlaybackStatusChanged");
    switch (_player.playbackStatus())
    {
    case PlaybackStatus::Paused:
        display(_notificationFactory.createPausedNotification(currentServiceName(), currentServiceLogo()));
        break;
    case PlaybackStatus::Playing:
        showSongNotification(_player.currentSong(), _localAlbumArt.url());
        break;
    default:
        break;
    }
}

void PlayerNotifications::onCurrentSongUrlChanged()
{
    LOG_TRACE(_logger, "onCurrentSongUrlChanged");
    showSongNotification(_player.currentSong(), _localAlbumArt.url());
}

void PlayerNotifications::showSongNotification(Song* song, const QString& localAlbumArtUrl)
{
    LOG_TRACE(_logger, "showSongNotification");
    if (song == nullptr)
        return;

    bool isReady = song->isValid();
    isReady &= _localAlbumArt.isReady(*song);
    isReady &= isPlaying();
    isReady &= _localAlbumArt.isReady(*song);
    if (isReady)
    {
        bool resume = song->uniqueId() == _previousSongId;
        _previousSongId = song->uniqueId();
        display(_notificationFactory.createSongNotification(currentServiceName(), song, localAlbumArtUrl, resume));
    }
}

bool PlayerNotifications::isPlaying() const
{
    return _player.playbackStatus() == PlaybackStatus::Playing;
}

const QString PlayerNotifications::currentServiceName() const
{
    auto currentService = _streamingServices.current();
    return currentService != nullptr ? currentService->name() : "";
}

const QString PlayerNotifications::currentServiceLogo() const
{
    auto currentService = _streamingServices.current();
    return currentService != nullptr ? currentService->logo() : "";
}

bool PlayerNotifications::isNotificationTypeEnabled(NotificationType type) const
{
    auto check = [](const Setting& setting) { return setting.isEnabled() && setting.value().toBool(); };

    bool isEnabled = false;

    auto settingKey = _player.serviceName() + "/notificationsEnabled";
    auto serviceNotificationsEnabled = _settings.store().value(settingKey, true).toBool();

    switch (type)
    {
    case NotificationType::Paused: {
        const Setting& setting = _settings.get(SettingKey::NOTIFICATIONS_PAUSED);
        isEnabled = check(setting) && serviceNotificationsEnabled;

        break;
    }
    case NotificationType::NewSong: {
        const Setting& setting = _settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
        isEnabled = check(setting) && serviceNotificationsEnabled;
        break;
    }
    case NotificationType::Resumed: {
        const Setting& setting = _settings.get(SettingKey::NOTIFICATIONS_RESUMED);
        isEnabled = check(setting) && serviceNotificationsEnabled;
        break;
    }
    }

    return isEnabled;
}

void PlayerNotifications::listen()
{
    LOG_TRACE(_logger, "listen");

    connect(&_player, &IPlayer::currentSongChanged, this, &PlayerNotifications::onCurrentSongChanged);
    connect(&_player, &IPlayer::playbackStatusChanged, this, &PlayerNotifications::onPlaybackStatusChanged);
    connect(&_localAlbumArt, &ILocalAlbumArt::urlChanged, this, &PlayerNotifications::onCurrentSongUrlChanged);
}