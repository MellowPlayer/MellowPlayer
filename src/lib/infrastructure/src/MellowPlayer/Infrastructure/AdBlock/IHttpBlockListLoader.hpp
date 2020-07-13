#pragma once

#include <QObject>
#include <MellowPlayer/Domain/AdBlock/IBlockListLoader.hpp>

namespace MellowPlayer::Infrastructure {
    class IHttpBlockListLoader : public Domain::IBlockListLoader
    {
        Q_OBJECT
    public:
        virtual ~IHttpBlockListLoader() = default;
    };
}
