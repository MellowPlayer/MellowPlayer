#pragma once

#include <MellowPlayer/Domain/Properties.hpp>
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>
#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
    class IUserScriptFactory;
    class StreamingService;
    class Player;
    class Players;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class NetworkProxy;
    class INetworkProxies;
}

namespace MellowPlayer::Presentation
{
    class StreamingServiceViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString logo READ logo CONSTANT)
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(Domain::Player* player READ player CONSTANT)
        Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(QString version READ version CONSTANT)
        Q_PROPERTY(QString authorName READ authorName CONSTANT)
        Q_PROPERTY(QString authorWebsite READ authorWebsite CONSTANT)
        Q_PROPERTY(int sortIndex READ sortIndex WRITE setSortIndex NOTIFY sortIndexChanged)
        Q_PROPERTY(UserScriptsViewModel* userScripts READ userScripts CONSTANT)
        Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor NOTIFY zoomFactorChanged)
        Q_PROPERTY(bool notificationsEnabled READ notificationsEnabled WRITE setNotificationsEnabled NOTIFY notificationsEnabledChanged)
        Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)
        Q_PROPERTY(QString previewImageUrl READ previewImageUrl WRITE setPreviewImageUrl NOTIFY previewImageUrlChanged)
        Q_PROPERTY(QString sourceCode READ sourceCode NOTIFY sourceCodeChanged)
        Q_PROPERTY(SettingsCategoryViewModel* settings READ settings CONSTANT)
        Q_PROPERTY(bool broken READ isBroken WRITE setBroken NOTIFY brokenChanged)
        Q_PROPERTY(bool hasKnownIssues READ hasKnownIssues NOTIFY hasKnownIssuesChanged)
        Q_PROPERTY(bool favorite READ isFavorite WRITE setFavorite NOTIFY favoriteChanged)
        CONSTANT_OBJECT_PROPERTY(Infrastructure::NetworkProxy, networkProxy)
    public:
        StreamingServiceViewModel(Domain::StreamingService& streamingService,
                                  Domain::ISettingsStore& settingsStore,
                                  Domain::IUserScriptFactory& userScriptFactory,
                                  Domain::Players& players,
                                  Infrastructure::INetworkProxies& networkProxies,
                                  ActiveThemeViewModel& themeViewModel,
                                  std::unique_ptr<Infrastructure::IHttpClient> httpClient,
                                  QObject* parent = nullptr);

        void checkForKnownIssues();

        QString logo() const;
        QString name() const;
        Domain::Player* player();
        QString url() const;
        QString version() const;
        QString authorName() const;
        QString authorWebsite() const;

        bool operator==(const StreamingServiceViewModel& rhs) const;
        bool operator!=(const StreamingServiceViewModel& rhs) const;

        Domain::StreamingService* streamingService() const;

        int sortIndex() const;
        void setSortIndex(int newOrder);

        QObject* userScripts();

        int zoomFactor() const;
        void setZoomFactor(int zoomFactor);

        bool notificationsEnabled() const;
        void setNotificationsEnabled(bool value);

        bool isActive() const;

        QString previewImageUrl() const;
        QString sourceCode() const;

        bool isBroken() const;
        bool hasKnownIssues() const;

        bool isFavorite() const;
        void setFavorite(bool value);

        SettingsCategoryViewModel* settings();

    public slots:
        void setUrl(const QString& newUrl);
        void setActive(bool isActive);
        void setBroken(bool value);

        void setPreviewImageUrl(QString previewImageUrl);
        QString getPreviewImageUrlForSave();

        void openKnownIssue();

    signals:
        void urlChanged(const QString&);
        void sortIndexChanged();
        void zoomFactorChanged();
        void notificationsEnabledChanged();
        void isActiveChanged();
        void previewImageUrlChanged();
        void sourceCodeChanged();
        void brokenChanged();
        void hasKnownIssuesChanged();
        void favoriteChanged();

    private:
        QString customUrlSettingsKey() const;
        QString sortIndexSettingKey() const;
        QString favoriteSettingKey() const;
        QString zoomFactorSettingsKey() const;
        QString notificationsEnabledSettingsKey() const;

        Domain::StreamingService& _streamingService;
        Domain::ISettingsStore& _settingsStore;
        std::shared_ptr<Domain::Player> _player;
        UserScriptsViewModel _userScriptsViewModel;
        int _zoomFactor;
        bool _isActive;
        QString _previewImageUrl;
        SettingsCategoryViewModel _settingsCategoryViewModel;
        Domain::ILogger& _logger;
        int _previewCount = 0;
        std::unique_ptr<Infrastructure::IHttpClient> _httpClient;
        bool _isBroken = false;
        QString _issueLink = "";
    };
}
