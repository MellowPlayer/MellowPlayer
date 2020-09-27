#pragma once

#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/SettingListModel.hpp>

namespace MellowPlayer::Domain
{
    class SettingsCategory;
}

namespace MellowPlayer::Presentation
{
    class ActiveThemeViewModel;

    class SettingsCategoryViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString icon READ icon CONSTANT)
        Q_PROPERTY(QString qmlComponent READ qmlComponent CONSTANT)
        Q_PROPERTY(QAbstractItemModel* settings READ settingsModel CONSTANT)
    public:
        SettingsCategoryViewModel(ActiveThemeViewModel& themeViewModel, Domain::SettingsCategory* settingsCategory = nullptr, QObject* parent = nullptr);

        virtual QString name() const;
        virtual QString icon() const;
        virtual QString qmlComponent() const;

        SettingListModel* settingsModel();

        Q_INVOKABLE void restoreDefaults();

    private:
        Domain::SettingsCategory* _settingsCategory;
        SettingListModel* _settingsListModel;
        SettingViewModelFactory _settingViewModelFactory;
    };

    class CustomSettingsCategoryViewModel : public SettingsCategoryViewModel
    {
        Q_OBJECT
    public:
        CustomSettingsCategoryViewModel(const QString& name,
                                        const QString& icon,
                                        const QString& qmlComponent,
                                        ActiveThemeViewModel& themeViewModel,
                                        QObject* parent = nullptr);

        QString name() const override;
        QString icon() const override;
        QString qmlComponent() const override;

    private:
        QString _name;
        QString _icon;
        QString _qmlComponent;
    };
}
