#pragma once

#include <QObject>
#include <QString>

namespace MellowPlayer::Domain
{
    enum class InstallationState
    {
        NotInstalled,
        UpToDate,
        Outdated
    };

    class IRemoteControlApplication : public QObject
    {
        Q_OBJECT
    public:
        using InstallCallback = std::function<void(bool success, const QString& errorMessage)>;

        virtual InstallationState checkInstallation() = 0;

        virtual QString logo() const = 0;
        virtual QString name() const = 0;
        virtual QString version() const = 0;

        virtual void install(const InstallCallback& installCallback) = 0;
        virtual bool isInstalling() const = 0;

        virtual void start() = 0;
        virtual void stop() = 0;

        bool isInstalled() const { return installationState() != InstallationState::NotInstalled; }
        bool isOutdated() const { return installationState() == InstallationState::Outdated; }

    protected:
        virtual InstallationState installationState() const = 0;

    signals:
        void installationStateChanged();
    };
}