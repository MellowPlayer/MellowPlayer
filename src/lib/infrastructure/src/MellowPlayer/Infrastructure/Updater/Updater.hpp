#pragma once

#include "UpdateChannel.hpp"
#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class ILogger;
    class Settings;
    class Setting;
}

namespace MellowPlayer::Infrastructure
{
    class AbstractPlatformUpdater;
    class ILatestRelease;
    class Release;

    class Updater : public QObject
    {
        Q_OBJECT
        Q_ENUMS(Status)
    public:
        Updater(ILatestRelease& releaseQuerier, Domain::Settings& settings, AbstractPlatformUpdater& platformUpdater);

        enum class Status
        {
            None,
            Checking,
            UpdateAvailable,
            Downloading,
            Installing,
            Installed,
            Failure
        };

        void setCurrentRelease(const Release* currentRelease);

        bool isUpdateAvailable() const;
        bool canInstall() const;
        const Release* latestRelease() const;
        Status status() const;

    public slots:
        void check();
        void install();
        void restart();

    signals:
        void updateAvailable();
        void noUpdateAvailable();
        void statusChanged();
        void progressUpdated(double progress);
        void installed();

    private slots:
        void onLatestReleaseReceived(const Release* release);
        void setStatus(Status status);
        void onDownloadFinished(bool succes);
        void onInstallFinished(bool succes);

    private:
        UpdateChannel getChannel() const;

        Domain::ILogger& _logger;
        ILatestRelease& _releaseQuerier;
        AbstractPlatformUpdater& _platformUpdater;
        Domain::Setting& _autoCheckEnabledSetting;
        Domain::Setting& _updateChannelSetting;
        bool _isUpdateAvailable = false;
        const Release* _currentRelease;
        const Release* _latestRelease = nullptr;
        Status _status = Status::None;
    };
}
