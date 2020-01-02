#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
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
    class ApplicationStatusFile : public Domain::Initializable
    {
        Q_OBJECT
    public:
        ApplicationStatusFile(Domain::IPlayer& currentPlayer);


        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

    private slots:
        void onCurrentPlayerUpdated();

    private:
        void create();
        void remove();

        QString fileName() const;
        QJsonObject serializePlayerStatus() const;
        QJsonObject serializeCurrentSong() const;
        void writeFile(const QString& fileName, const QByteArray& data) const;

        Domain::IPlayer& currentPlayer;
        Domain::ILogger& logger;
        QJsonObject previousPlayerStatus;
    };
}
