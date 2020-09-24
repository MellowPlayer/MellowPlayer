#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <QFile>
#include <QJsonDocument>

using namespace MellowPlayer::Infrastructure;

QJsonDocument SettingsSchemaLoader::load() const
{
    QFile jsonFile(":/MellowPlayer/Infrastructure/Settings/settings-schema.json");
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
