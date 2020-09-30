#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class EnumSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        EnumSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        virtual QStringList values() const;

        QString qmlComponent() override;
    };
}
