#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Infrastructure
{
    class IQtApplication;
}

namespace MellowPlayer::Application
{
    class FontsSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit FontsSetup(Infrastructure::IQtApplication& qtApplication);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Infrastructure::IQtApplication& _qtApplication;
    };
}
