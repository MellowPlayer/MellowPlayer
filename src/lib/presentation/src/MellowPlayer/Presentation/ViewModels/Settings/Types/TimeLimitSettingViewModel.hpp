#pragma once

#include "EnumSettingViewModel.hpp"
#include <MellowPlayer/Domain/ListeningHistory/TimeLimits.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

class TimeLimitSettingStrings : public QObject
{
    Q_OBJECT
public:
    QString today() const
    {
        return tr("Today");
    };
    QString yesterday() const
    {
        return tr("Yesterday");
    };
    QString lastWeek() const
    {
        return tr("Last week");
    };
    QString lastMonth() const
    {
        return tr("Last month");
    };
    QString lastYear() const
    {
        return tr("Last year");
    };
    QString never() const
    {
        return tr("Never");
    };
};

namespace MellowPlayer::Presentation
{
    class TimeLimitSettingViewModel : public EnumSettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        TimeLimitSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QVariant value() const override;
        QStringList values() const override;
        QString qmlComponent() override;

    signals:
        void valueChanged();

    public slots:
        virtual void setValue(QVariant value);

    private:
        void registerEnumTranslation(Domain::TimeLimits value, const QString& translation);

        QMap<QString, Domain::TimeLimits> _stringToEnum;
        QMap<Domain::TimeLimits, QString> _enumToString;
    };
}
