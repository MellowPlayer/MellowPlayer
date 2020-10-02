#pragma once

#include <MellowPlayer/Domain/UserScripts/UserScripts.hpp>
#include <MellowPlayer/Presentation/Models/UserScriptListModel.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class IUserScriptsViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool hasScripts READ hasScripts NOTIFY hasScriptsChanged)
        Q_PROPERTY(QQmlObjectListModelBase* model READ model CONSTANT)

    public:
        using QObject::QObject;

        virtual QQmlObjectListModelBase* model() = 0;
        virtual bool hasScripts() const = 0;

        virtual Q_INVOKABLE QString generateUniqueName(const QString& path) const = 0;
        virtual Q_INVOKABLE bool isValidName(const QString& name) const = 0;
        virtual Q_INVOKABLE bool add(const QString& name, const QString& sourcePath) = 0;
        virtual Q_INVOKABLE void remove(const QString& name) = 0;

    signals:
        void hasScriptsChanged();
    };

    class UserScriptsViewModel : public IUserScriptsViewModel
    {
        Q_OBJECT
        Q_PROPERTY(bool hasScripts READ hasScripts NOTIFY hasScriptsChanged)
        Q_PROPERTY(QQmlObjectListModelBase* model READ model CONSTANT)
    public:
        UserScriptsViewModel(const QString& serviceName,
                             Domain::IUserScriptFactory& userScriptFactory,
                             Domain::ISettingsStore& settingsStore,
                             QObject* parent = nullptr);

        QQmlObjectListModelBase* model();
        bool hasScripts() const;

        Q_INVOKABLE QString generateUniqueName(const QString& path) const;
        Q_INVOKABLE bool isValidName(const QString& name) const;
        Q_INVOKABLE bool add(const QString& name, const QString& sourcePath);
        Q_INVOKABLE void remove(const QString& name);



    private:
        void create(Domain::IUserScript* userScriptModel);

        Domain::UserScripts _userScripts;
        UserScriptListModel _model;
    };

    class NullUserScriptsViewModel : public IUserScriptsViewModel
    {
        Q_OBJECT

    public:
        using IUserScriptsViewModel::IUserScriptsViewModel;

        QQmlObjectListModelBase* model() override
        {
            return nullptr;
        }

        bool hasScripts() const override
        {
            return false;
        }

        QString generateUniqueName(const QString&) const override
        {
            return "";
        }

        bool isValidName(const QString&) const override
        {
            return false;
        }

        bool add(const QString&, const QString&) override
        {
            return false;
        }

        void remove(const QString&) override
        {
        }
    };
}
