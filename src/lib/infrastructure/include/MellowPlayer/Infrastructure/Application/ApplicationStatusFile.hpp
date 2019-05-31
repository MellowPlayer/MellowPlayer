#pragma once

#include <QObject>
#include <QJsonObject>

namespace MellowPlayer::Domain
{
    class IPlayer;
    class ILocalAlbumArt;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class ApplicationStatusFile : public QObject
    {
        Q_OBJECT
    public:
        ApplicationStatusFile(Domain::IPlayer& currentPlayer, Domain::ILocalAlbumArt& localAlbumArt);

        void create();
        void remove();

    private slots:
        void OnCurrentPlayerUpdated();

    private:
        QString fileName() const;
        QJsonObject serializePlayerStatus() const;
        QJsonObject serializeCurrentSong() const;
        void writeFile(const QString& fileName, const QByteArray& data) const;

        Domain::IPlayer& currentPlayer;
        Domain::ILocalAlbumArt& localAlbumArt;
        Domain::ILogger& logger;
        QJsonObject previousPlayerStatus;
    };
}
