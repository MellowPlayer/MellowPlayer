#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/ListeningHistory/SqlLiteListeningHistoryDatabase.hpp>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

SqlLiteListeningHistoryDatabase::SqlLiteListeningHistoryDatabase() : _logger(Loggers::logger("SqlLiteListeningHistoryDataProvider"))
{
}

SqlLiteListeningHistoryDatabase::~SqlLiteListeningHistoryDatabase()
{
    _database.close();
}

bool SqlLiteListeningHistoryDatabase::openDatabase()
{
    auto path = getDatabasePath();
    LOG_DEBUG(_logger, "opening listening history db: " + path)
    _database.setDatabaseName(path);
    if (!_database.open())
    {
        LOG_WARN(_logger, "connection with database failed: " + path)
        return false;
    }
    LOG_DEBUG(_logger, "connected to database: " + path)
    return true;
}

int SqlLiteListeningHistoryDatabase::add(const ListeningHistoryEntry& entry)
{
    QSqlQuery query;
    query.prepare("INSERT INTO song (songUniqueId, songTitle, artist, album, "
                  "artUrl, serviceName, time) VALUES (:songUniqueId, :songTitle, "
                  ":artist, :album, :artUrl, :serviceName, :time)");
    query.bindValue(":songUniqueId", entry.songUniqueId);
    query.bindValue(":songTitle", entry.songTitle);
    query.bindValue(":artist", entry.artist);
    query.bindValue(":album", entry.album);
    query.bindValue(":artUrl", entry.artUrl);
    query.bindValue(":serviceName", entry.serviceName);
    query.bindValue(":time", entry.time);

    if (!query.exec())
    {
        LOG_WARN(_logger, "failed to add listening history entry to db: " + query.lastError().text());
        return -1;
    }
    else
        return query.lastInsertId().toInt();
}

void SqlLiteListeningHistoryDatabase::clear()
{
    QSqlQuery query;
    query.prepare("DELETE FROM song");

    if (!query.exec())
        LOG_WARN(_logger, "failed to clear listening history: " + query.lastError().text());
}

void SqlLiteListeningHistoryDatabase::remove(const QString& filterKey, const QString& filterValue)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM song WHERE %1=(:%1)").arg(filterKey));
    query.bindValue(QString(":%1").arg(filterKey), filterValue);

    if (!query.exec())
        LOG_WARN(_logger, "failed to clear listening history: " + query.lastError().text());
}

void SqlLiteListeningHistoryDatabase::removeMany(const QList<int>& identifiers)
{
    QStringList idStrings;
    foreach (int id, identifiers)
        idStrings << QString::number(id);
    QString numberList = idStrings.join(",");

    QSqlQuery query;
    QString queryString = QString("DELETE FROM song WHERE id IN (%1)").arg(numberList);

    if (!query.exec(queryString))
        LOG_WARN(_logger, "failed to clear listening history: " + query.lastError().text());
}

QList<ListeningHistoryEntry> SqlLiteListeningHistoryDatabase::toList() const
{
    QList<ListeningHistoryEntry> retVal;

    QSqlQuery query("SELECT * FROM song ORDER BY time");
    int idId = query.record().indexOf("id");
    int idUniqueId = query.record().indexOf("songUniqueId");
    int idTitle = query.record().indexOf("songTitle");
    int idArtist = query.record().indexOf("artist");
    int idAlbum = query.record().indexOf("album");
    int idArtUrl = query.record().indexOf("artUrl");
    int idServiceName = query.record().indexOf("serviceName");
    int idTime = query.record().indexOf("time");

    while (query.next())
    {
        ListeningHistoryEntry entry;
        entry.songUniqueId = query.value(idUniqueId).toString();
        entry.songTitle = query.value(idTitle).toString();
        entry.artist = query.value(idArtist).toString();
        entry.album = query.value(idAlbum).toString();
        entry.artUrl = query.value(idArtUrl).toString();
        entry.serviceName = query.value(idServiceName).toString();
        entry.time = query.value(idTime).toString();
        entry.id = query.value(idId).toInt();
        retVal.append(entry);
    }

    return retVal;
}

bool SqlLiteListeningHistoryDatabase::initDatabase()
{
    if (_database.tables().count() == 0)
    {
        LOG_DEBUG(_logger, "creating database");
        QSqlQuery query;
        query.prepare("CREATE TABLE song(id INTEGER PRIMARY KEY, songUniqueId "
                      "TEXT, songTitle TEXT, artist TEXT, album TEXT, "
                      "artUrl TEXT, serviceName TEXT, time TEXT);");
        if (!query.exec())
        {
            LOG_WARN(_logger, "failed to create song table: " + query.lastError().text());
            return false;
        }
    }
    return true;
}

bool SqlLiteListeningHistoryDatabase::initialize()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    if (openDatabase())
        return initDatabase();
    return false;
}

QString SqlLiteListeningHistoryDatabase::getDatabasePath()
{
    return FileHelper::appDataDirectory() + "history.db";
}
