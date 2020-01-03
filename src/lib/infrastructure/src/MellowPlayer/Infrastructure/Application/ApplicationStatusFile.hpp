#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Domain/RemoteControl/IApplicationStatusFile.hpp>
#include <QJsonObject>
#include <QObject>

namespace MellowPlayer::Domain
{
    class IPlayer;
    class ILocalAlbumArt;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class ApplicationStatusFile : public Domain::IApplicationStatusFile
    {
        Q_OBJECT
    public:
        explicit ApplicationStatusFile(Domain::IPlayer& currentPlayer);

        void create() override;
        void remove() override;

    private slots:
        void onCurrentPlayerUpdated();

    private:
        QString fileName() const;
        QJsonObject serializePlayerStatus() const;
        QJsonObject serializeCurrentSong() const;
        void writeFile(const QString& fileName, const QByteArray& data) const;

        Domain::IPlayer& _currentPlayer;
        Domain::ILogger& _logger;
        QJsonObject _previousPlayerStatus;
    };
}
