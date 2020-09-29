#include <MellowPlayer/Presentation/ViewModels/Settings/Types/TimeLimitSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

TimeLimitSettingViewModel::TimeLimitSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
    TimeLimitSettingStrings strings;
    registerEnumTranslation(TimeLimits::Today, strings.today());
    registerEnumTranslation(TimeLimits::Yesterday, strings.yesterday());
    registerEnumTranslation(TimeLimits::LastWeek, strings.lastWeek());
    registerEnumTranslation(TimeLimits::LastMonth, strings.lastMonth());
    registerEnumTranslation(TimeLimits::LastYear, strings.lastYear());
    registerEnumTranslation(TimeLimits::Never, strings.never());
}

void TimeLimitSettingViewModel::registerEnumTranslation(TimeLimits value, const QString& translation)
{
    _stringToEnum[translation] = value;
    _enumToString[value] = translation;
}

QVariant TimeLimitSettingViewModel::value() const
{
    TimeLimits limit = static_cast<TimeLimits>(_setting.value().toInt());
    return _enumToString[limit];
}

void TimeLimitSettingViewModel::setValue(QVariant value)
{
    TimeLimits limit = _stringToEnum[value.toString()];
    _setting.setValue(static_cast<int>(limit));
}

QString TimeLimitSettingViewModel::qmlComponent()
{
    return "Delegates/EnumSettingDelegate.qml";
}

QStringList TimeLimitSettingViewModel::values() const
{
    return _stringToEnum.keys();
}
