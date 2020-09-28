#pragma once

#include <MellowPlayer/Domain/RemoteControl/IRemoteControl.hpp>
#include <MellowPlayer/Presentation/Models/QQmlObjectListModel.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

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

    class RemoteControlErrorViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString title READ title CONSTANT)
        Q_PROPERTY(QString message READ message CONSTANT)
    public:
        RemoteControlErrorViewModel(const QString& title, const QString& message, QObject* parent = nullptr) : QObject(parent), _title(title), _message(message)
        {
        }

        QString title() const
        {
            return _title;
        }
        QString message() const
        {
            return _message;
        }

    private:
        QString _title;
        QString _message;
    };

    class RemoteControlViewModel : public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractListModel* states READ states CONSTANT)
        Q_PROPERTY(QObject* appInfo READ appInfo CONSTANT)
        Q_PROPERTY(int currentStateIndex READ currentStateIndex NOTIFY currentStateIndexChanged)
        Q_PROPERTY(bool autoStartEnabled READ isAutoStartEnabled WRITE setAutoStartEnabled NOTIFY autoStartEnabledChanged)
        Q_PROPERTY(RemoteControlErrorViewModel* error READ error NOTIFY errorChanged)
    public:
        explicit RemoteControlViewModel(Domain::IRemoteControl& remoteControl);

        QQmlObjectListModel<RemoteControlStateViewModel>* states();
        RemoteControlApplicationInfoViewModel* appInfo();
        int currentStateIndex() const;
        bool isAutoStartEnabled() const;
        void setAutoStartEnabled(bool value);
        RemoteControlErrorViewModel* error() const;

        Q_INVOKABLE void activate();
        Q_INVOKABLE void deactivate();
        Q_INVOKABLE void install();
        Q_INVOKABLE void start();
        Q_INVOKABLE void stop();

    signals:
        void currentStateIndexChanged();
        void errorChanged();
        void autoStartEnabledChanged();

    private:
        void addState(RemoteControlStateViewModel* state);
        QString currentStateName() const;
        void onFailedToStart();
        void onError(const QString& title, const QString& message);

        Domain::IRemoteControl& _remoteControl;
        Domain::IRemoteControlApplication& _remoteControlApplication;
        RemoteControlApplicationInfoViewModel _appInfo;
        QMap<QString, RemoteControlStateViewModel*> _stateByName;
        QQmlObjectListModel<RemoteControlStateViewModel> _states;
        RemoteControlErrorViewModel* _error{nullptr};
    };
}