#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class CacheViewModel;
}

namespace MellowPlayer::Application
{
    class CacheCleanup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit CacheCleanup(Presentation::CacheViewModel& cache);

        void cleanUp() override;

    private:
        Presentation::CacheViewModel& _cache;
    };
}
