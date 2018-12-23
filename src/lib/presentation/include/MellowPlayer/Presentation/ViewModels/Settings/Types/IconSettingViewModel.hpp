#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class IconSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
    public:
        explicit IconSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString getValue() const;
        QString qmlComponent() override;
    signals:
        void valueChanged();

    public slots:
        void setValue(QString value);

    protected slots:
        void onValueChanged() override;
    };
}

