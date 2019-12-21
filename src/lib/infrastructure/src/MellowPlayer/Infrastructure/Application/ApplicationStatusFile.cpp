#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>
#include <MellowPlayer/Infrastructure/Application/ApplicationStatusFile.hpp>
#include <QtCore/QDir>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Domain;

ApplicationStatusFile::ApplicationStatusFile(IPlayer& currentPlayer) : currentPlayer(currentPlayer), logger(Loggers::logger("ApplicationStatusFile"))
{
    connect(&currentPlayer, &IPlayer::currentSongChanged, this, &ApplicationStatusFile::OnCurrentPlayerUpdated);
    connect(&currentPlayer, &IPlayer::playbackStatusChanged, this, &ApplicationStatusFile::OnCurrentPlayerUpdated);
}

void ApplicationStatusFile::create()
{
    OnCurrentPlayerUpdated();
}

void ApplicationStatusFile::remove()
{
    QFile::remove(fileName());
}

QString ApplicationStatusFile::fileName() const
{
    return QDir::tempPath() + QDir::separator() + "mellowplayer-status.json";
}

void ApplicationStatusFile::OnCurrentPlayerUpdated()
{
    auto playerStatus = serializePlayerStatus();
    if (playerStatus != previousPlayerStatus)
    {
        auto json = QJsonDocument(playerStatus).toJson();
        LOG_TRACE(logger, "Updating player status <" << fileName() << ">: " << json.toStdString());
        writeFile(fileName(), json);
        previousPlayerStatus = playerStatus;
    }
}
QJsonObject ApplicationStatusFile::serializePlayerStatus() const
{
    QJsonObject playerStatus;

    playerStatus["isPlaying"] = currentPlayer.isPlaying();
    playerStatus["currentSong"] = serializeCurrentSong();
    playerStatus["serviceName"] = currentPlayer.serviceName();

    return playerStatus;
}
QJsonObject ApplicationStatusFile::serializeCurrentSong() const
{
    QJsonObject jsonSong;
    auto* currentSong = currentPlayer.currentSong();

    if (currentSong)
    {
        connect(currentSong, &Song::isFavoriteChanged, this, &ApplicationStatusFile::OnCurrentPlayerUpdated, Qt::UniqueConnection);

        jsonSong["artist"] = currentSong->artist();
        jsonSong["title"] = currentSong->title();
        jsonSong["album"] = currentSong->album();
        jsonSong["artUrl"] = currentSong->artUrl();
        jsonSong["isFavorite"] = currentSong->isFavorite();
    }
    else
    {
        jsonSong["artist"] = "";
        jsonSong["title"] = "";
        jsonSong["album"] = "";
        jsonSong["artUrl"] = "";
        jsonSong["isFavorite"] = false;
    }

    return jsonSong;
}
void ApplicationStatusFile::writeFile(const QString& fileName, const QByteArray& data) const
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
    {
        LOG_WARN(logger, "Failed to write player status to " << fileName);
        return;
    }
    file.write(data);
    file.close();
}

void ApplicationStatusFile::initialize(const ResultCallback& resultCallback)
{
    create();
    resultCallback(true);
}

void ApplicationStatusFile::cleanUp()
{
    remove();
}

QString ApplicationStatusFile::toString() const
{
    return "ApplicationStatusFile";
}
