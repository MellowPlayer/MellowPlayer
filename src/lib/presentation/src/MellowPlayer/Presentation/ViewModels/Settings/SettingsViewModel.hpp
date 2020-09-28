#pragma once

#include "SettingsCategoryViewModel.hpp"
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/SettingsCategoryListModel.hpp>
#include <QObject>

namespace MellowPlayer::Domain
{
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class SettingViewModel;
    class ActiveThemeViewModel;

    class SettingsViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* categories READ categories CONSTANT)
    public:
        SettingsViewModel(Domain::Settings& settings, ActiveThemeViewModel& themeViewModel);

        SettingsCategoryListModel* categories() const;

        Q_INVOKABLE SettingViewModel* get(int key);
        Q_INVOKABLE void restoreDefaults();
        Q_INVOKABLE void restoreCategoryDefaults(const QString& category);

    private:
        Domain::Settings& _settings;
        SettingViewModelFactory _factory;
        SettingsCategoryListModel* _categories;
    };
}
