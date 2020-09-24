#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <stdexcept>

using namespace std;
using namespace MellowPlayer::Domain;

SettingsCategory::SettingsCategory(const SettingsCategory::Data& categoryData, Settings* appSettings) : QObject(appSettings), _data(categoryData)
{
    for (int i = 0; i < _data.parameters.count(); ++i)
    {
        QJsonObject parameterObj = _data.parameters.at(i).toObject();
        Setting::Data settingData;
        settingData.name = parameterObj.value("name").toString();
        settingData.toolTip = parameterObj.value("tooltip").toString();
        settingData.type = parameterObj.value("type").toString();
        settingData.key = parameterObj.value("key").toString();
        settingData.defaultValue = parameterObj.value("default").toVariant();
        settingData.enableCondition = parameterObj.value("enabled").toString();
        _settings.append(new Setting(*appSettings, *this, settingData));
    }
}

void SettingsCategory::resolveDependencies()
{
    for (Setting* setting : _settings)
        setting->resolveDependency();
}

const QString& SettingsCategory::name() const
{
    return _data.name;
}

const QString& SettingsCategory::icon() const
{
    return _data.icon;
}

const QString& SettingsCategory::key() const
{
    return _data.key;
}

const QList<Setting*>& SettingsCategory::toList() const
{
    return _settings;
}

Setting& SettingsCategory::get(const QString& key) const
{
    for (Setting* param : _settings)
        if (param->key() == key)
            return *param;
    throw runtime_error("Unknown setting: " + _data.key.toStdString() + "/" + key.toStdString());
}

QString SettingsCategory::toJavascriptObject()
{
    QJsonDocument document;
    QJsonObject jsonObject;
    for (auto* setting : toList())
    {
        QString type = setting->type().toLower();
        if (type == "bool")
            jsonObject[setting->key()] = setting->value().toBool();
        else if (type == "int")
            jsonObject[setting->key()] = setting->value().toInt();
        else
            jsonObject[setting->key()] = setting->value().toString();
    }
    document.setObject(jsonObject);
    return QString::fromUtf8(document.toJson(QJsonDocument::Compact));
}

void SettingsCategory::restoreDefaults()
{
    for (Setting* setting : _settings)
        setting->restoreDefaults();
}
