#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Domain
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class BoolSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
    public:
        BoolSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QVariant value() const override;
        void setValue(const QVariant& value) override;

        QString qmlComponent() override;
    };
}
