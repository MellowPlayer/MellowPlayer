#pragma once

#include "SettingViewModel.hpp"
#include <QColor>

namespace MellowPlayer::Presentation
{
    class ColorSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
    public:
        ColorSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);
        QString qmlComponent() override;
    };
}
