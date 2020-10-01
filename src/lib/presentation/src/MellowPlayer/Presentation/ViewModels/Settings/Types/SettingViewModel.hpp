#pragma once

#include <QObject>

namespace MellowPlayer::Domain
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class SettingViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString toolTip READ toolTip CONSTANT)
        Q_PROPERTY(QString type READ type CONSTANT)
        Q_PROPERTY(QString qmlComponent READ qmlComponent CONSTANT)
        Q_PROPERTY(bool isEnabled READ isEnabled NOTIFY isEnabledChanged)
        Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    public:
        SettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString name() const;
        QString toolTip() const;
        QString type() const;
        virtual QString qmlComponent() = 0;

        virtual QVariant value() const;
        bool isEnabled() const;

    public slots:
        virtual void setValue(const QVariant& value);

    signals:
        void isEnabledChanged();
        void valueChanged();

    protected:
        Domain::Setting& _setting;
    };
}
