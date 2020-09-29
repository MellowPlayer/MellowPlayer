#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class StringSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
    public:
        StringSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString qmlComponent() override;
    };
}
