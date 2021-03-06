#pragma once

#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

namespace MellowPlayer::Infrastructure
{
    class Updater;
}

namespace MellowPlayer::Presentation
{
    class UpdaterViewModel : public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(QString url READ url CONSTANT)
        Q_PROPERTY(QString status READ status NOTIFY statusChanged)
        Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
        Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)
        Q_PROPERTY(bool installEnabled READ installEnabled NOTIFY installEnabledChanged)
        Q_PROPERTY(bool restartEnabled READ restartEnabled NOTIFY restartEnabledChanged)
        Q_PROPERTY(double progress READ progress NOTIFY progressChanged)
    public:
        UpdaterViewModel(Infrastructure::Updater& updater);

        QString url() const;
        QString status() const;
        bool busy() const;
        bool visible() const;
        bool installEnabled() const;
        bool restartEnabled() const;
        double progress() const;

        Q_INVOKABLE void close();
        Q_INVOKABLE void check();
        Q_INVOKABLE void install();
        Q_INVOKABLE void restart();

    signals:
        void visibleChanged();
        void installEnabledChanged();
        void restartEnabledChanged();
        void progressChanged();
        void statusChanged();
        void busyChanged();

    private slots:
        void setVisible(bool visible);
        void setInstallEnabled(bool enabled);
        void setRestartEnabled(bool enabled);
        void setProgress(double progress);
        void onUpdateAvailable();
        void onNoUpdateAvailable();
        void onProgressUpdated(double progress);
        void onInstalled();

    private:
        Infrastructure::Updater& _updater;
        bool _visible = false;
        bool _installEnabled = false;
        bool _restartEnabled = false;
        double _progress = -1;
    };
}
