#pragma once

#include "SettingViewModel.hpp"
#include <MellowPlayer/Infrastructure/Updater/UpdateChannel.hpp>

namespace MellowPlayer::Presentation
{
    class UpdateChannelSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        UpdateChannelSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QVariant value() const override;
        QStringList values() const;
        QString qmlComponent() override;

    public slots:
        void setValue(const QVariant& value) override;

    private:
        UpdateChannelStringer _stringer;
    };
}
