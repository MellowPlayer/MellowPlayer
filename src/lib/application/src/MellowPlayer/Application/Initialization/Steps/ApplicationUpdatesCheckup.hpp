#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class UpdaterViewModel;
}

namespace MellowPlayer::Application
{
    class ApplicationUpdatesCheckup : public Domain::Initializable
    {
    Q_OBJECT
    public:
        explicit ApplicationUpdatesCheckup(Presentation::UpdaterViewModel& updater);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::UpdaterViewModel& _updater;
    };
}
