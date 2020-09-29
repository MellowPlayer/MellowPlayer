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

        QString qmlComponent() override;
    };
}
