#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class ScalingFactorSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(int minValue READ minValue CONSTANT)
        Q_PROPERTY(int maxValue READ maxValue CONSTANT)
        Q_PROPERTY(int step READ step CONSTANT)
        Q_PROPERTY(QString suffix READ suffix CONSTANT)
    public:
        ScalingFactorSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        int minValue() const;
        int maxValue() const;
        int step() const;
        QString suffix() const;

        QString qmlComponent() override;
    };
}
