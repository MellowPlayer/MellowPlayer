#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <QVersionNumber>
#include <stdexcept>

using namespace std;
using namespace MellowPlayer::Domain;

Setting::Setting(Settings& settings, SettingsCategory& category, const Setting::Data& settingData)
        : QObject(&category), _settingsStore(settings.store()), _settings(settings), _category(category), _data(settingData)
{
}

void Setting::resolveDependency()
{
    QString key(_data.enableCondition);
    key = key.replace("!", "");
    key = key.split("==")[0].trimmed();

    if (key.isEmpty())
        return;

    try
    {
        _parentSetting = &_settings.get(key);
        connect(_parentSetting, &Setting::valueChanged, this, &Setting::onParentValueChanged);
    }
    catch (const runtime_error&)
    {
        return;
    }
}

void Setting::restoreDefaults()
{
    setValue(_data.defaultValue);
}

const QString& Setting::key() const
{
    return _data.key;
}

const QString& Setting::name() const
{
    return _data.name;
}

const QString& Setting::type() const
{
    return _data.type;
}

QVariant Setting::defaultValue() const
{
    return _data.defaultValue;
}

void Setting::setDefaultValue(QVariant defaultValue)
{
    _data.defaultValue = defaultValue;
}

QVariant Setting::value() const
{
    return _settingsStore.value(getFullKey(), _data.defaultValue);
}

void Setting::setValue(const QVariant& newValue)
{
    if (newValue != value())
    {
        _settingsStore.setValue(getFullKey(), newValue);
        emit valueChanged();
    }
}

bool Setting::isEnabled() const
{
    QString cond = _data.enableCondition;

    if (cond.contains("qtVersion >="))
    {
        QVersionNumber requiredQtVersion = QVersionNumber::fromString(cond.split(">=")[1].trimmed().toLower());
        QVersionNumber qtVersion(QT_VERSION_MAJOR, QT_VERSION_MINOR);
        return qtVersion >= requiredQtVersion;
    }

    if (_parentSetting == nullptr)
        return true;

    if (cond.contains("=="))
    {
        QString value = cond.split("==")[1].trimmed().toLower();
        QString parentValue = _parentSetting->value().toString();
        return parentValue.trimmed().toLower() == value;
    }
    else
    {
        bool parentValue = _parentSetting->value().toBool();
        if (cond.startsWith("!"))
            return !parentValue;
        return parentValue;
    }
}

QString Setting::getFullKey() const
{
    return _category.key() + "/" + _data.key;
}

void Setting::onParentValueChanged()
{
    emit isEnabledChanged();
}

const QString& Setting::toolTip() const
{
    return _data.toolTip;
}
