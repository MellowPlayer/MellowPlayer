#pragma once

#include "EnumSettingViewModel.hpp"
#include <MellowPlayer/Infrastructure/Updater/UpdateChannel.hpp>

namespace MellowPlayer::Presentation
{
    class UpdateChannelSettingViewModel : public EnumSettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        UpdateChannelSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QVariant value() const override;
        QStringList values() const override;
        QString qmlComponent() override;

    public slots:
        void setValue(const QVariant& value) override;

    private:
        UpdateChannelStringer _stringer;
    };
}
