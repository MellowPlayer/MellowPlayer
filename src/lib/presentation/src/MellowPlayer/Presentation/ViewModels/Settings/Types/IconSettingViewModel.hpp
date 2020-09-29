#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class IconSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
    public:
        explicit IconSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString qmlComponent() override;
    };
}
