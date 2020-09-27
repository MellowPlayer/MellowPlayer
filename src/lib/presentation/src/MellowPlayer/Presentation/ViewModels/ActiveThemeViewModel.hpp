#pragma once

#include <MellowPlayer/Domain/Theme/Theme.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QMap>
#include <QObject>

namespace MellowPlayer::Domain
{
    class StreamingService;
    class StreamingServices;
    class Setting;
    class Settings;
    class IThemeLoader;
}

namespace MellowPlayer::Presentation
{
    class ActiveThemeViewModel : public QObject, public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(bool dark READ isDark NOTIFY isDarkChanged)
        Q_PROPERTY(QString accent READ accent NOTIFY accentChanged)
        Q_PROPERTY(QString background READ background NOTIFY backgroundChanged)
        Q_PROPERTY(QString foreground READ foreground NOTIFY foregroundChanged)
        Q_PROPERTY(QString primary READ primary NOTIFY primaryChanged)
        Q_PROPERTY(QString primaryForeground READ primaryForeground NOTIFY primaryForegroundChanged)
        Q_PROPERTY(QString secondary READ secondary NOTIFY secondaryChanged)
        Q_PROPERTY(QString secondaryForeground READ secondaryForeground NOTIFY secondaryForegroundChanged)
    public:
        ActiveThemeViewModel(Domain::StreamingServices& streamingServices,
                       Domain::Settings& settings,
                       Domain::IThemeLoader& themeLoader,
                             IQmlSingletons& qmlSingletons);

        bool isDark() const;
        QString accent() const;
        QString background() const;
        QString foreground() const;
        QString primary() const;
        QString primaryForeground() const;
        QString secondary() const;
        QString secondaryForeground() const;
        QStringList availableThemes() const;

        Q_INVOKABLE double colorScaleFactor(const QString& color) const;
        Q_INVOKABLE bool isDark(const QString& color) const;

        Domain::Theme customTheme() const;
        Domain::Theme theme(const QString& themeName) const;

    signals:
        void isDarkChanged();
        void accentChanged();
        void backgroundChanged();
        void foregroundChanged();
        void primaryChanged();
        void primaryForegroundChanged();
        void secondaryChanged();
        void secondaryForegroundChanged();

    private slots:
        void update();
        void onCurrentServiceChanged(Domain::StreamingService* streamingService);

    private:
        void setAccent(const QString& value);
        void setBackground(const QString& value);
        void setForeground(const QString& value);
        void setPrimary(const QString& value);
        void setPrimaryForeground(const QString& value);
        void setSecondary(const QString& value);
        void setSecondaryForeground(const QString& value);
        void fromTheme(const Domain::Theme& newTheme);
        void collectThemes();

        Domain::StreamingServices& _streamingServices;
        Domain::IThemeLoader& _loader;
        Domain::Setting& _accentColorSetting;
        Domain::Setting& _themeSetting;
        Domain::Setting& _backgroundSetting;
        Domain::Setting& _foregroundSetting;
        Domain::Setting& _primaryBackgroundSetting;
        Domain::Setting& _primaryForegroundSetting;
        Domain::Setting& _secondaryBackgroundSetting;
        Domain::Setting& _secondaryForegroundSetting;
        Domain::Theme _currentTheme;
        QMap<QString, Domain::Theme> _availableThemes;

        bool isAdaptiveTheme() const;
    };
}
