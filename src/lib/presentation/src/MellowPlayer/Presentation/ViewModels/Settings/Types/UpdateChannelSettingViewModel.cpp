#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/UpdateChannelSettingViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

UpdateChannelSettingViewModel::UpdateChannelSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString UpdateChannelSettingViewModel::value() const
{
    UpdateChannel channel = static_cast<UpdateChannel>(_setting.value().toInt());
    return _stringer.toTranslatedString(channel);
}

QStringList UpdateChannelSettingViewModel::values() const
{
    return QStringList() << _stringer.toTranslatedString(UpdateChannel::Stable) << _stringer.toTranslatedString(UpdateChannel::Continuous);
}

QString UpdateChannelSettingViewModel::qmlComponent()
{
    return "Delegates/EnumSettingDelegate.qml";
}

void UpdateChannelSettingViewModel::setValue(QString value)
{
    _setting.setValue(static_cast<int>(_stringer.fromString(value)));
}

void UpdateChannelSettingViewModel::onValueChanged()
{
    emit valueChanged();
}
