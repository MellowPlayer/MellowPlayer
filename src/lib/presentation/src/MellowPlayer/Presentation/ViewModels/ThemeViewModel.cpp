#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/Theme/IThemeLoader.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>

#include <QDebug>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

ThemeViewModel::ThemeViewModel(StreamingServices& streamingServices,
                               Settings& settings,
                               IThemeLoader& themeLoader,
                               std::shared_ptr<IContextProperties> contextProperties)
        : ContextProperty("theme", this, contextProperties),
          _streamingServices(streamingServices),
          _loader(themeLoader),
          _accentColorSetting(settings.get(SettingKey::APPEARANCE_ACCENT)),
          _themeSetting(settings.get(SettingKey::APPEARANCE_THEME)),
          _backgroundSetting(settings.get(SettingKey::APPEARANCE_BACKGROUND)),
          _foregroundSetting(settings.get(SettingKey::APPEARANCE_FOREGROUND)),
          _primaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_BACKGROUND)),
          _primaryForegroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_FOREGROUND)),
          _secondaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_BACKGROUND)),
          _secondaryForegroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_FOREGROUND)),
          _currentTheme(customTheme())
{
    _themeSetting.setDefaultValue(BuildConfig::getDefaultTheme());
    connect(&streamingServices, &StreamingServices::currentChanged, this, &ThemeViewModel::onCurrentServiceChanged);
    connect(&_accentColorSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_themeSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_backgroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_foregroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_primaryBackgroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_primaryForegroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_secondaryBackgroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&_secondaryForegroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);

    collectThemes();
    update();
}

bool ThemeViewModel::isDark() const
{
    return isDark(_currentTheme.background);
}

QString ThemeViewModel::accent() const
{
    return _currentTheme.accent;
}

QString ThemeViewModel::background() const
{
    return _currentTheme.background;
}

QString ThemeViewModel::foreground() const
{
    return _currentTheme.foreground;
}

QString ThemeViewModel::primary() const
{
    return _currentTheme.primary;
}

QString ThemeViewModel::primaryForeground() const
{
    return _currentTheme.primaryForeground;
}

QString ThemeViewModel::secondary() const
{
    return _currentTheme.secondary;
}

QString ThemeViewModel::secondaryForeground() const
{
    return _currentTheme.secondaryForeground;
}

void ThemeViewModel::update()
{
    StreamingService* currentService = _streamingServices.current();
    QString current = _themeSetting.value().toString();
    if (currentService != nullptr && isAdaptiveTheme() && !currentService->theme().isEmpty())
    {
        Theme theme = currentService->theme();
        _availableThemes["Adaptive"] = theme;
        fromTheme(theme);
    }
    else if (isAdaptiveTheme())
        fromTheme(_availableThemes["Default"]);
    else if (current == "Custom")
        fromTheme(customTheme());
    else
        fromTheme(_availableThemes[current]);
}

bool ThemeViewModel::isAdaptiveTheme() const
{
    return _themeSetting.value().toString() == "Adaptive";
}

void ThemeViewModel::onCurrentServiceChanged(StreamingService* streamingService)
{
    connect(streamingService, &StreamingService::themeChanged, this, &ThemeViewModel::update, Qt::UniqueConnection);

    if (streamingService != nullptr)
        update();
}

void ThemeViewModel::setAccent(const QString& value)
{
    if (value == _currentTheme.accent)
        return;

    _currentTheme.accent = value;
    emit accentChanged();
}

void ThemeViewModel::setBackground(const QString& value)
{
    if (value == _currentTheme.background)
        return;

    _currentTheme.background = value;
    emit backgroundChanged();
    emit isDarkChanged();
}

void ThemeViewModel::setForeground(const QString& value)
{
    if (value == _currentTheme.foreground)
        return;

    _currentTheme.foreground = value;
    emit foregroundChanged();
}

void ThemeViewModel::setPrimary(const QString& value)
{
    if (value == _currentTheme.primary)
        return;

    _currentTheme.primary = value;
    emit primaryChanged();
}

void ThemeViewModel::setPrimaryForeground(const QString& value)
{
    if (value == _currentTheme.primaryForeground)
        return;

    _currentTheme.primaryForeground = value;
    emit primaryForegroundChanged();
}

void ThemeViewModel::setSecondary(const QString& value)
{
    if (value == _currentTheme.secondary)
        return;

    _currentTheme.secondary = value;
    emit secondaryChanged();
}

void ThemeViewModel::setSecondaryForeground(const QString& value)
{
    if (value == _currentTheme.secondaryForeground)
        return;

    _currentTheme.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void ThemeViewModel::fromTheme(const Theme& newTheme)
{
    setAccent(newTheme.accent);
    setBackground(newTheme.background);
    setForeground(newTheme.foreground);
    setPrimary(newTheme.primary);
    setPrimaryForeground(newTheme.primaryForeground);
    setSecondary(newTheme.secondary);
    setSecondaryForeground(newTheme.secondaryForeground);
}

double ThemeViewModel::colorScaleFactor(const QString& color) const
{
    const int lightnessMax = 164;
    const float darkerFactor = 1.05f;
    const float lighterFactor = 1.2f;

    if (QColor(color).lightness() > lightnessMax)
        return darkerFactor;
    return lighterFactor;
}

bool ThemeViewModel::isDark(const QString& color) const
{
    QColor c(color);
    int lightness = c.lightness();
    int ffCount = 0;
    if (c.red() > 250)
        ffCount++;
    if (c.green() > 250)
        ffCount++;
    if (c.blue() > 250)
        ffCount++;
    return lightness < 164 && ffCount < 2;
}

Theme ThemeViewModel::customTheme() const
{
    return Theme{_accentColorSetting.value().toString(),
                 _backgroundSetting.value().toString(),
                 _foregroundSetting.value().toString(),
                 _primaryBackgroundSetting.value().toString(),
                 _primaryForegroundSetting.value().toString(),
                 _secondaryBackgroundSetting.value().toString(),
                 _secondaryForegroundSetting.value().toString()};
}

void ThemeViewModel::collectThemes()
{
    _availableThemes["Adaptive"] = _currentTheme;
    _availableThemes["Ubuntu"] = _loader.load(":/MellowPlayer/Presentation/themes/Ubuntu.json");
    _availableThemes["Breeze"] = _loader.load(":/MellowPlayer/Presentation/themes/Breeze.json");
    _availableThemes["BreezeDark"] = _loader.load(":/MellowPlayer/Presentation/themes/BreezeDark.json");
    _availableThemes["Midna"] = _loader.load(":/MellowPlayer/Presentation/themes/Midna.json");
    _availableThemes["MidnaDark"] = _loader.load(":/MellowPlayer/Presentation/themes/MidnaDark.json");
    _availableThemes["Custom"] = customTheme();
    _availableThemes["Default"] = _loader.load(":/MellowPlayer/Presentation/themes/Default.json");
}

QStringList ThemeViewModel::availableThemes() const
{
    QStringList themes = _availableThemes.keys();
    themes.sort();
    return themes;
}

Theme ThemeViewModel::theme(const QString& themeName) const
{
    return _availableThemes[themeName];
}
