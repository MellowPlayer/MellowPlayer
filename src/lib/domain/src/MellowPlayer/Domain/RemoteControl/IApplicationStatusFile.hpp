#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class IApplicationStatusFile : public QObject
    {
    public:
        virtual void create() = 0;
        virtual void remove() = 0;
    };
}