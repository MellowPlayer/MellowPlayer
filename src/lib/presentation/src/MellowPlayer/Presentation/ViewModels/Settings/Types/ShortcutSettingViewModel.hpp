#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class ShortcutSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
    public:
        ShortcutSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString qmlComponent() override;
        Q_INVOKABLE QString keySequenceToString(int key, int modifiers);
        Q_INVOKABLE bool isValidKeySequence(int key, int modifiers);
    };
}
