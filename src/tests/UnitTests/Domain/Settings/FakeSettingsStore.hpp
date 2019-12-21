#pragma once

#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakeSettingsStore : public ISettingsStore
    {
    public:
        QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override
        {
            if (_values.contains(key))
                return _values[key];
            return defaultValue;
        }

        void setValue(const QString& key, const QVariant& value) override
        {
            _values[key] = value;
        }

        void clear() override
        {
            _values.clear();
        }

    private:
        QMap<QString, QVariant> _values;
    };
}