#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <memory>

namespace MellowPlayer::Domain
{
    class IPlayerBase;
    class StreamingService;
    class StreamingServices;

    class Players : public QObject
    {
        Q_OBJECT
    public:
        explicit Players(StreamingServices& streamingServices);

        std::shared_ptr<IPlayerBase> get(const QString& serviceName) const;

    private slots:
        void onServiceAdded(Domain::StreamingService* service);

    private:
        QMap<QString, std::shared_ptr<IPlayerBase>> _players;
    };
}
