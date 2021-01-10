#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>
#include <functional>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ZoomViewModel::ZoomViewModel(ISettingsStore& settingsStore)
        : _settingsStore(settingsStore), _logger(Loggers::logger("ZoomViewModel"))
{
    _value = settingsStore.value("zoom", 1.0).toDouble();
}

double ZoomViewModel::value() const
{
    return _value;
}

void ZoomViewModel::setValue(double value)
{
    if (value < 0.25)
        value = 0.25;
    else if (value > 5)
        value = 5;

    if (value != _value)
    {
        _value = value;
        _settingsStore.setValue("zoom", value);
        LOG_DEBUG(_logger, "Value changed: " << _value);
        emit valueChanged();
    }
}

void ZoomViewModel::increment()
{
    setValue(value() + 0.25);
}

void ZoomViewModel::decrement()
{
    setValue(value() - 0.25);
}

void ZoomViewModel::reset()
{
    setValue(1);
}
