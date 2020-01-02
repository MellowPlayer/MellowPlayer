#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <QtQml/QtQml>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingsViewModel::SettingsViewModel(Settings& settings, ThemeViewModel& themeViewModel, IContextProperties& contextProperties)
        : ContextProperty("_settings", this, contextProperties),
          _settings(settings),
          _factory(themeViewModel),
          _categories(new SettingsCategoryListModel(this, "name"))
{
    for (SettingsCategory* category : settings.categories())
    {
        if (category->key() != "private")
            _categories->append(new SettingsCategoryViewModel(themeViewModel, category, this));
    }
    _categories->append(new CustomSettingsCategoryViewModel("Streaming Services", u8"\ue405", "SettingsPages/ServiceSettingsPage.qml", themeViewModel, this));
    _categories->append(new CustomSettingsCategoryViewModel("Cache", u8"\ue872", "SettingsPages/CacheSettingsPage.qml", themeViewModel, this));
}

SettingViewModel* SettingsViewModel::get(int key)
{
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = _settings.get(settingKey);
    return _factory.create(setting, this);
}

SettingsCategoryListModel* SettingsViewModel::categories() const
{
    return _categories;
}

void SettingsViewModel::restoreDefaults()
{
    _settings.restoreDefaults();
}

void SettingsViewModel::registerTo(IQmlApplicationEngine& qmlApplicationEngine)
{
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "SettingKey", "SettingKey cannot be instantiated from QML");
    ContextProperty::registerTo(qmlApplicationEngine);
}
