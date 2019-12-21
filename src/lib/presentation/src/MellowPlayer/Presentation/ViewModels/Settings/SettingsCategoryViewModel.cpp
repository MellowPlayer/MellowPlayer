#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingsCategoryViewModel::SettingsCategoryViewModel(ThemeViewModel& themeViewModel, SettingsCategory* settingsCategory, QObject* parent)
        : QObject(parent), _settingsCategory(settingsCategory), _settingsListModel(new SettingListModel(this, "name")), _settingViewModelFactory(themeViewModel)
{
    if (settingsCategory != nullptr)
        for (Setting* setting : settingsCategory->toList())
            _settingsListModel->append(_settingViewModelFactory.create(*setting, this));
}

QString SettingsCategoryViewModel::name() const
{
    return _settingsCategory != nullptr ? _settingsCategory->name() : "";
}

QString SettingsCategoryViewModel::icon() const
{
    return _settingsCategory != nullptr ? _settingsCategory->icon() : "";
}

QString SettingsCategoryViewModel::qmlComponent() const
{
    return "SettingsPages/AutomaticSettingsPage.qml";
}

SettingListModel* SettingsCategoryViewModel::settingsModel()
{
    return _settingsListModel;
}

void SettingsCategoryViewModel::restoreDefaults()
{
    _settingsCategory->restoreDefaults();
}

CustomSettingsCategoryViewModel::CustomSettingsCategoryViewModel(const QString& name,
                                                                 const QString& icon,
                                                                 const QString& qmlComponent,
                                                                 ThemeViewModel& themeViewModel,
                                                                 QObject* parent)
        : SettingsCategoryViewModel(themeViewModel, nullptr, parent), _name(name), _icon(icon), _qmlComponent(qmlComponent)
{
}

QString CustomSettingsCategoryViewModel::name() const
{
    return _name;
}

QString CustomSettingsCategoryViewModel::icon() const
{
    return _icon;
}

QString CustomSettingsCategoryViewModel::qmlComponent() const
{
    return _qmlComponent;
}
