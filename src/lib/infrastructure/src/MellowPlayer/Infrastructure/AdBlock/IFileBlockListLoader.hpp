#pragma once

#include <QObject>
#include <MellowPlayer/Domain/AdBlock/IBlockListLoader.hpp>

namespace MellowPlayer::Infrastructure {
    class IFileBlockListLoader : public Domain::IBlockListLoader
    {
        Q_OBJECT
    public:
        virtual ~IFileBlockListLoader() = default;
    };
}
