#pragma once

#include "IMprisService.hpp"

namespace MellowPlayer::Presentation
{
    class NullMprisService : public IMprisService
    {
    public:
        void initialize(const ResultCallback& resultCallback) override;
        virtual bool start();
    };
}
