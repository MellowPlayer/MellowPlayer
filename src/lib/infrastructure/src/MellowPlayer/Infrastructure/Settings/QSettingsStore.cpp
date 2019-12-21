#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

QSettingsStore::QSettingsStore() : qSettings_(make_unique<QSettings>("MellowPlayer", "MellowPlayer3")), logger_(Loggers::logger("SettingsStore"))
{
    LOG_DEBUG(logger_, "Settings file: " << qSettings_->fileName().toStdString());
}

void QSettingsStore::setOrganizationName(const QString& orgName)
{
    qSettings_ = make_unique<QSettings>(orgName, "MellowPlayer3");
    LOG_DEBUG(logger_, "Settings file: " << qSettings_->fileName().toStdString());
}

void QSettingsStore::clear()
{
    qSettings_->clear();
}

QVariant QSettingsStore::value(const QString& key, const QVariant& defaultValue) const
{
    return qSettings_->value(key, defaultValue);
}

void QSettingsStore::setValue(const QString& key, const QVariant& value)
{
    qSettings_->setValue(key, value);
}
