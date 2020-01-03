#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

QSettingsStore::QSettingsStore() : _qSettings(make_unique<QSettings>("MellowPlayer", "MellowPlayer3")), _logger(Loggers::logger("SettingsStore"))
{
    LOG_INFO(_logger, "Settings file: " << _qSettings->fileName().toStdString());
}

void QSettingsStore::setOrganizationName(const QString& orgName)
{
    _qSettings = make_unique<QSettings>(orgName, "MellowPlayer3");
    LOG_DEBUG(_logger, "Settings file: " << _qSettings->fileName().toStdString());
}

void QSettingsStore::clear()
{
    _qSettings->clear();
}

QVariant QSettingsStore::value(const QString& key, const QVariant& defaultValue) const
{
    return _qSettings->value(key, defaultValue);
}

void QSettingsStore::setValue(const QString& key, const QVariant& value)
{
    _qSettings->setValue(key, value);
}
