#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <QtQml>
#include <stdexcept>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingsViewModel::SettingsViewModel(Settings& settings, ActiveThemeViewModel& themeViewModel)
        : _settings(settings),
          _factory(themeViewModel),
          _categories(new SettingsCategoryListModel(this, "name"))
{
    for (SettingsCategory* category : settings.categories())
    {
        if (category->key() != "private")
            _categories->append(new SettingsCategoryViewModel(themeViewModel, category, this));
    }
    _categories->append(new CustomSettingsCategoryViewModel("Remote Control", u8"\ue8c7", "SettingsPages/RemoteControlSettingsPage.qml", themeViewModel, this));
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

void SettingsViewModel::restoreCategoryDefaults(const QString& categoryName)
{
    for (auto& category: _settings.categories())
    {
        if (category->name() == categoryName)
            category->restoreDefaults();
    }
}
