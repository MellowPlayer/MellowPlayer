#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class IPlayer;
    class ILocalAlbumArt;
    class ILogger;
}

namespace MellowPlayer::Presentation
{
    class Mpris2Root;
    class Mpris2Player;
    class IMainWindow;

    class MprisStartup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        MprisStartup(Domain::IPlayer& player, Domain::ILocalAlbumArt& localAlbumArt, IMainWindow& window);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

    private:
        bool start();

        static QString SERVICE_NAME;
        static QString OBJECT_NAME;

        Domain::ILogger& _logger;
        std::unique_ptr<QObject> _parent;
        QObject* _mpris2Root;
        QObject* _mpris2Player;
        QString _serviceName;
    };
}