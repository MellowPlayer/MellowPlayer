#pragma once

#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <QSettings>
#include <memory>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class QSettingsStore : public Domain::ISettingsStore
    {
    public:
        QSettingsStore();

        void setOrganizationName(const QString& orgName);

        void clear() override;

        QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;
        void setValue(const QString& key, const QVariant& value) override;

    private:
        std::unique_ptr<QSettings> _qSettings;
        Domain::ILogger& _logger;
    };
}
