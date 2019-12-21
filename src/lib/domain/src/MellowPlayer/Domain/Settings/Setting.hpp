#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
    class Settings;
    class SettingsCategory;

    class Setting : public QObject
    {
        Q_OBJECT
    public:
        struct Data
        {
            QString name;
            QString key;
            QString toolTip;
            QString type;
            QVariant defaultValue;
            QString enableCondition;
        };

        Setting(Settings& settings, SettingsCategory& category, const Data& settingData);

        void resolveDependency();
        void restoreDefaults();

        const QString& key() const;
        const QString& name() const;
        const QString& toolTip() const;
        const QString& type() const;
        QVariant defaultValue() const;
        void setDefaultValue(QVariant defaultValue);

        QVariant value() const;
        void setValue(const QVariant& newValue);

        bool isEnabled() const;

    signals:
        void isEnabledChanged();
        void valueChanged();

    private slots:
        void onParentValueChanged();

    private:
        QString getFullKey() const;

        ISettingsStore& _settingsStore;
        Settings& _settings;
        SettingsCategory& _category;
        Data _data;
        //        bool notOperator_ = false;
        Setting* _parentSetting = nullptr;
    };
}
