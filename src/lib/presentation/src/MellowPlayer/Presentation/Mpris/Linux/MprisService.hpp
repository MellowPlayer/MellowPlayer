#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Mpris/IMprisService.hpp>
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

    class MprisService : public IMprisService
    {
    public:
        MprisService(Domain::IPlayer& player, Domain::ILocalAlbumArt& localAlbumArt, IMainWindow& window);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

    private:
        bool start();

        static QString SERVICE_NAME;
        static QString OBJECT_NAME;

        Domain::ILogger& logger_;
        std::unique_ptr<QObject> parent_;
        QObject* mpris2Root_;
        QObject* mpris2Player_;
        QString serviceName_;
    };
}

