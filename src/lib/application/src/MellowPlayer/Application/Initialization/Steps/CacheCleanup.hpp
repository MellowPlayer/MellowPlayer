#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class ApplicationViewModel;
}

namespace MellowPlayer::Application
{
    class CacheCleanup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit CacheCleanup(Presentation::ApplicationViewModel& applicationViewModel);

        void cleanUp() override;

    private:
        Presentation::ApplicationViewModel& _applicationViewModel;
    };
}
