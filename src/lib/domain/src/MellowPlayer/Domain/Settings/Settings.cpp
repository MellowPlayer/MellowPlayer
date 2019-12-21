#include <MellowPlayer/Domain/Settings/ISettingsSchemaLoader.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

using namespace std;
using namespace MellowPlayer::Domain;

Settings::Settings(ISettingsSchemaLoader& configurationLoader, ISettingsStore& settingsStore) : _settingsStore(settingsStore)
{
    QJsonDocument jsonDocument = configurationLoader.load();
    QJsonObject rootObject = jsonDocument.object();
    QJsonArray categoriesArray = rootObject.value("categories").toArray();

    for (int i = 0; i < categoriesArray.count(); ++i)
    {
        QJsonObject categoryObject = categoriesArray.at(i).toObject();
        SettingsCategory::Data data;
        data.name = categoryObject.value("name").toString();
        data.icon = categoryObject.value("icon").toString();
        data.key = categoryObject.value("key").toString();
        data.parameters = categoryObject.value("settings").toArray();
        _categories.append(new SettingsCategory(data, this));
    }

    for (SettingsCategory* category : _categories)
        category->resolveDependencies();
}

const QList<SettingsCategory*>& Settings::categories() const
{
    return _categories;
}

SettingsCategory& Settings::category(const QString& key) const
{
    for (SettingsCategory* category : _categories)
        if (category->key() == key)
            return *category;
    throw runtime_error("Unknown category: " + key.toStdString());
}

Setting& Settings::get(const QString& key) const
{
    QStringList tokens = key.split("/");

    if (tokens.count() != 2)
        throw runtime_error("Malformed setting key: " + key.toStdString());

    QString categoryKey = tokens[0];
    QString parameterKey = tokens[1];

    auto& c = category(categoryKey);
    return c.get(parameterKey);
}

ISettingsStore& Settings::store() const
{
    return _settingsStore;
}

Setting& Settings::get(SettingKey::Keys key)
{
    return get(SettingKey::toString(key));
}

void Settings::restoreDefaults()
{
    for (SettingsCategory* category : _categories)
        category->restoreDefaults();
}
