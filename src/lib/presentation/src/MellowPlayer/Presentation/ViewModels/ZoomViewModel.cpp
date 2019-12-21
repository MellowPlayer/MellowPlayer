#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <functional>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ZoomViewModel::ZoomViewModel(IContextProperties &contextProperties, ISettingsStore& settingsStore)
        : ContextProperty("_zoom", this, contextProperties),
          _settingsStore(settingsStore)
{
    setValue(settingsStore.value("zoom", 1.0).toDouble());
}

double ZoomViewModel::value() const
{
    return _value;
}

void ZoomViewModel::setValue(double value)
{
    if (value < 0.5)
        value = 0.5;
    else if (value > 3)
        value = 3;

    if (value != _value)
    {
        _value = value;
        _settingsStore.setValue("zoom", value);
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
