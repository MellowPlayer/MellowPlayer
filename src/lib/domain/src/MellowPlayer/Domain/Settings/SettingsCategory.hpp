#pragma once

#include <QJsonArray>
#include <QList>
#include <QObject>

namespace MellowPlayer::Domain
{
    class Settings;
    class Setting;
    class ISettingsStore;

    class SettingsCategory : public QObject
    {
        Q_OBJECT
    public:
        struct Data
        {
            QJsonArray parameters;
            QString name;
            QString icon;
            QString key;
        };

        SettingsCategory(const Data& data, Settings* appSettings);
        void resolveDependencies();

        void restoreDefaults();

        const QString& name() const;
        const QString& icon() const;
        const QString& key() const;
        const QList<Setting*>& toList() const;

        Setting& get(const QString& key) const;

        QString toJavascriptObject();

    private:
        Data _data;
        QList<Setting*> _settings;
    };
}
