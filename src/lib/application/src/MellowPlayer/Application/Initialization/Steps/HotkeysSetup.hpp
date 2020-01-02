#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class IHotkeys;
}

namespace MellowPlayer::Application
{
    class HotkeysSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit HotkeysSetup(Presentation::IHotkeys& hotkeys);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;

    private:
        Presentation::IHotkeys& _hotkeys;
    };
}
