#pragma once

#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>
#include <MellowPlayer/Presentation/Models/QQmlObjectListModel.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QtCore/QObject>

namespace MellowPlayer::Presentation
{
    class RemoteControlStateViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString qmlComponent READ qmlComponent CONSTANT)
    public:
        RemoteControlStateViewModel(const QString& name, const QString& qmlComponent);

        QString name() const;
        QString qmlComponent() const;

    private:
        QString _name;
        QString _qmlComponent;
    };

    class RemoteControlApplicationInfoViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString homePage READ homePage CONSTANT)
        Q_PROPERTY(QString logo READ logo CONSTANT)
        Q_PROPERTY(QString url READ url CONSTANT)
        Q_PROPERTY(QString minimumRequiredVersion READ minimumRequiredVersion CONSTANT)
        Q_PROPERTY(QString version READ version NOTIFY versionChanged)
    public:
        explicit RemoteControlApplicationInfoViewModel(Domain::IRemoteControlApplication& remoteControlApplication);

        QString name() const;
        QString homePage() const;
        QString logo() const;
        QString url() const;
        QString minimumRequiredVersion() const;
        QString version() const;

    signals:
        void versionChanged();

    private:
        Domain::IRemoteControlApplication& _remoteControlApplication;
    };

    class RemoteControlViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractListModel* states READ states CONSTANT)
        Q_PROPERTY(QObject* appInfo READ appInfo CONSTANT)
        Q_PROPERTY(int currentStateIndex READ currentStateIndex NOTIFY currentStateIndexChanged)
        Q_PROPERTY(bool autoStartEnabled READ isAutoStartEnabled WRITE setAutoStartEnabled NOTIFY autoStartEnabledChanged)
    public:
        explicit RemoteControlViewModel(Domain::IRemoteControl& remoteControl, IContextProperties& contextProperties);

        QQmlObjectListModel<RemoteControlStateViewModel>* states();
        RemoteControlApplicationInfoViewModel* appInfo();
        int currentStateIndex() const;
        bool isAutoStartEnabled() const;
        void setAutoStartEnabled(bool value);

        Q_INVOKABLE void activate();
        Q_INVOKABLE void deactivate();
        Q_INVOKABLE void install();
        Q_INVOKABLE void start();
        Q_INVOKABLE void stop();

    signals:
        void currentStateIndexChanged();
        void error(const QString& title, const QString& message);
        void autoStartEnabledChanged();

    private:
        void addState(RemoteControlStateViewModel* state);
        QString currentStateName() const;

        Domain::IRemoteControl& _remoteControl;
        Domain::IRemoteControlApplication& _remoteControlApplication;
        RemoteControlApplicationInfoViewModel _appInfo;
        QMap<QString, RemoteControlStateViewModel*> _stateByName;
        QQmlObjectListModel<RemoteControlStateViewModel> _states;
    };
}