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
    class IPlayerBase;
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
    using IPlayerBase = Domain::IPlayerBase;
    using NetworkProxy = Infrastructure::NetworkProxy;

    class IStreamingServiceViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString logo READ logo CONSTANT)
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(IPlayerBase* player READ player CONSTANT)
        Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(QString version READ version CONSTANT)
        Q_PROPERTY(QString authorName READ authorName CONSTANT)
        Q_PROPERTY(QString authorWebsite READ authorWebsite CONSTANT)
        Q_PROPERTY(int sortIndex READ sortIndex WRITE setSortIndex NOTIFY sortIndexChanged)
        Q_PROPERTY(IUserScriptsViewModel* userScripts READ userScripts CONSTANT)
        Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor NOTIFY zoomFactorChanged)
        Q_PROPERTY(bool notificationsEnabled READ notificationsEnabled WRITE setNotificationsEnabled NOTIFY notificationsEnabledChanged)
        Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)
        Q_PROPERTY(QString previewImageUrl READ previewImageUrl WRITE setPreviewImageUrl NOTIFY previewImageUrlChanged)
        Q_PROPERTY(QString sourceCode READ sourceCode NOTIFY sourceCodeChanged)
        Q_PROPERTY(SettingsCategoryViewModel* settings READ settings CONSTANT)
        Q_PROPERTY(bool broken READ isBroken WRITE setBroken NOTIFY brokenChanged)
        Q_PROPERTY(bool hasKnownIssues READ hasKnownIssues NOTIFY hasKnownIssuesChanged)
        Q_PROPERTY(bool favorite READ isFavorite WRITE setFavorite NOTIFY favoriteChanged)
        CONSTANT_OBJECT_PROPERTY(NetworkProxy, networkProxy)
    public:
        using QObject::QObject;
        virtual void checkForKnownIssues() = 0;
        virtual QString logo() const = 0;
        virtual QString name() const = 0;
        virtual Domain::IPlayerBase* player() = 0;
        virtual QString url() const = 0;
        virtual QString version() const = 0;
        virtual QString authorName() const = 0;
        virtual QString authorWebsite() const = 0;
        virtual bool operator==(const IStreamingServiceViewModel& rhs) const = 0;
        virtual bool operator!=(const IStreamingServiceViewModel& rhs) const = 0;
        virtual Domain::StreamingService* streamingService() const = 0;
        virtual int sortIndex() const = 0;
        virtual void setSortIndex(int newOrder) = 0;
        virtual IUserScriptsViewModel* userScripts() = 0;
        virtual int zoomFactor() const = 0;
        virtual void setZoomFactor(int zoomFactor) = 0;
        virtual bool notificationsEnabled() const = 0;
        virtual void setNotificationsEnabled(bool value) = 0;
        virtual bool isActive() const = 0;
        virtual QString previewImageUrl() const = 0;
        virtual QString sourceCode() const = 0;
        virtual bool isBroken() const = 0;
        virtual bool hasKnownIssues() const = 0;
        virtual bool isFavorite() const = 0;
        virtual void setFavorite(bool value) = 0;
        virtual SettingsCategoryViewModel* settings() = 0;

    public slots:
        virtual void setUrl(const QString& newUrl) = 0;
        virtual void setActive(bool isActive) = 0;
        virtual void setBroken(bool value) = 0;
        virtual void setPreviewImageUrl(QString previewImageUrl) = 0;
        virtual QString getPreviewImageUrlForSave() = 0;
        virtual void openKnownIssue() = 0;

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
    };

    class StreamingServiceViewModel : public IStreamingServiceViewModel
    {
        Q_OBJECT
    public:
        StreamingServiceViewModel(Domain::StreamingService& streamingService,
                                  Domain::ISettingsStore& settingsStore,
                                  Domain::IUserScriptFactory& userScriptFactory,
                                  Domain::Players& players,
                                  Infrastructure::INetworkProxies& networkProxies,
                                  ThemeViewModel& themeViewModel,
                                  std::unique_ptr<Infrastructure::IHttpClient> httpClient,
                                  QObject* parent = nullptr);

        void checkForKnownIssues() override;

        QString logo() const override;
        QString name() const override;
        Domain::IPlayerBase* player() override;
        QString url() const override;
        QString version() const override;
        QString authorName() const override;
        QString authorWebsite() const override;

        bool operator==(const IStreamingServiceViewModel& rhs) const override;
        bool operator!=(const IStreamingServiceViewModel& rhs) const override;

        Domain::StreamingService* streamingService() const override;

        int sortIndex() const override;
        void setSortIndex(int newOrder) override;

        IUserScriptsViewModel* userScripts() override;

        int zoomFactor() const override;
        void setZoomFactor(int zoomFactor) override;

        bool notificationsEnabled() const override;
        void setNotificationsEnabled(bool value) override;

        bool isActive() const override;

        QString previewImageUrl() const override;
        QString sourceCode() const override;

        bool isBroken() const override;
        bool hasKnownIssues() const override;

        bool isFavorite() const override;
        void setFavorite(bool value) override;

        SettingsCategoryViewModel* settings() override;

    public slots:
        void setUrl(const QString& newUrl) override;
        void setActive(bool isActive) override;
        void setBroken(bool value) override;

        void setPreviewImageUrl(QString previewImageUrl) override;
        QString getPreviewImageUrlForSave() override;

        void openKnownIssue() override;

    private:
        QString customUrlSettingsKey() const;
        QString sortIndexSettingKey() const;
        QString favoriteSettingKey() const;
        QString zoomFactorSettingsKey() const;
        QString notificationsEnabledSettingsKey() const;

        Domain::StreamingService& _streamingService;
        Domain::ISettingsStore& _settingsStore;
        std::shared_ptr<Domain::IPlayerBase> _player;
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

    class NullStreamingServiceViewModel : public IStreamingServiceViewModel
    {
        Q_OBJECT
    public:
        NullStreamingServiceViewModel(QObject* parent= nullptr);

        void checkForKnownIssues() override;
        QString logo() const override;
        QString name() const override;
        IPlayerBase* player() override;
        QString url() const override;
        QString version() const override;
        QString authorName() const override;
        QString authorWebsite() const override;
        bool operator==(const IStreamingServiceViewModel& rhs) const override;
        bool operator!=(const IStreamingServiceViewModel& rhs) const override;
        Domain::StreamingService* streamingService() const override;
        int sortIndex() const override;
        void setSortIndex(int newOrder) override;
        IUserScriptsViewModel* userScripts() override;
        int zoomFactor() const override;
        void setZoomFactor(int zoomFactor) override;
        bool notificationsEnabled() const override;
        void setNotificationsEnabled(bool value) override;
        bool isActive() const override;
        QString previewImageUrl() const override;
        QString sourceCode() const override;
        bool isBroken() const override;
        bool hasKnownIssues() const override;
        bool isFavorite() const override;
        void setFavorite(bool value) override;
        SettingsCategoryViewModel* settings() override;
        void setUrl(const QString& newUrl) override;
        void setActive(bool isActive) override;
        void setBroken(bool value) override;
        void setPreviewImageUrl(QString previewImageUrl) override;
        QString getPreviewImageUrlForSave() override;
        void openKnownIssue() override;
    };
}
