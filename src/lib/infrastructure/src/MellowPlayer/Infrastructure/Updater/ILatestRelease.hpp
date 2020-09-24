#pragma once

#include "UpdateChannel.hpp"
#include <QObject>

namespace MellowPlayer::Infrastructure
{
    class Release;

    class ILatestRelease : public QObject
    {
        Q_OBJECT
    public:
        virtual ~ILatestRelease() = default;

        virtual void setChannel(UpdateChannel channel) = 0;
        virtual void get() = 0;

    signals:
        void received(const Release *release);
    };
}
