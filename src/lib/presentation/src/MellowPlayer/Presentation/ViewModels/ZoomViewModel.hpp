#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
}

namespace MellowPlayer::Presentation
{
    class ZoomViewModel: public QObject, public ContextProperty
    {
        Q_OBJECT
        Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    public:
        explicit ZoomViewModel(std::shared_ptr<IContextProperties> contextProperties, Domain::ISettingsStore& settingsStore);

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
    };
}
