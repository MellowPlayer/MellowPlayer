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

ApplicationStatusFile::ApplicationStatusFile(IPlayer& currentPlayer) : _currentPlayer(currentPlayer), _logger(Loggers::logger("ApplicationStatusFile"))
{

}

void ApplicationStatusFile::create()
{
#ifdef Q_OS_WIN
    connect(&_currentPlayer, &IPlayer::currentSongChanged, this, &ApplicationStatusFile::onCurrentPlayerUpdated);
    connect(&_currentPlayer, &IPlayer::playbackStatusChanged, this, &ApplicationStatusFile::onCurrentPlayerUpdated);

    onCurrentPlayerUpdated();

    LOG_DEBUG(_logger, "Writing player status changes to " << fileName());
    LOG_INFO(_logger, "Application Status File: " << fileName());
#endif
}

void ApplicationStatusFile::remove()
{
#ifdef Q_OS_WIN
    QFile::remove(fileName());

    disconnect(&_currentPlayer, &IPlayer::currentSongChanged, this, &ApplicationStatusFile::onCurrentPlayerUpdated);
    disconnect(&_currentPlayer, &IPlayer::playbackStatusChanged, this, &ApplicationStatusFile::onCurrentPlayerUpdated);

    LOG_DEBUG(_logger, fileName() << " removed and player status monitoring disabled");
#endif
}

QString ApplicationStatusFile::fileName() const
{
    return QDir::tempPath() + QDir::separator() + "mellowplayer-status.json";
}

void ApplicationStatusFile::onCurrentPlayerUpdated()
{
    auto playerStatus = serializePlayerStatus();
    if (playerStatus != _previousPlayerStatus)
    {
        auto json = QJsonDocument(playerStatus).toJson();
        LOG_TRACE(_logger, "Updating player status <" << fileName() << ">: " << json.toStdString());
        writeFile(fileName(), json);
        _previousPlayerStatus = playerStatus;
    }
}
QJsonObject ApplicationStatusFile::serializePlayerStatus() const
{
    QJsonObject playerStatus;

    playerStatus["isPlaying"] = _currentPlayer.isPlaying();
    playerStatus["currentSong"] = serializeCurrentSong();
    playerStatus["serviceName"] = _currentPlayer.serviceName();

    return playerStatus;
}
QJsonObject ApplicationStatusFile::serializeCurrentSong() const
{
    QJsonObject jsonSong;
    auto* currentSong = _currentPlayer.currentSong();

    if (currentSong)
    {
        connect(currentSong, &Song::isFavoriteChanged, this, &ApplicationStatusFile::onCurrentPlayerUpdated, Qt::UniqueConnection);

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
        LOG_WARN(_logger, "Failed to write player status to " << fileName);
        return;
    }
    file.write(data);
    file.close();
}
