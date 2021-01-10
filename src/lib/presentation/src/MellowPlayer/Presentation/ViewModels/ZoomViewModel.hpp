#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <QObject>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
}

namespace MellowPlayer::Presentation
{
    class ZoomViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    public:
        explicit ZoomViewModel(Domain::ISettingsStore& settingsStore);

        double value() const;
        void setValue(double value);

        Q_INVOKABLE void increment();
        Q_INVOKABLE void decrement();
        Q_INVOKABLE void reset();

    signals:
        void valueChanged();

    private:
        Domain::ISettingsStore& _settingsStore;
        double _value;
        Domain::ILogger& _logger;
    };
}
