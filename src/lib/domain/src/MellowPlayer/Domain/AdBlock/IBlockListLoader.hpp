#pragma once

#include <QObject>

namespace MellowPlayer::Domain {
    class IBlockListLoader : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IBlockListLoader() = default;

        virtual void load(QString source, const std::function<void(QList<QString>)>) const = 0;
    };
}
