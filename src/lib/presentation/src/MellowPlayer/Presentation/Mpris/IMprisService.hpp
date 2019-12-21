#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>
namespace MellowPlayer::Presentation
{
    class IMprisService : public Domain::IInitializable
    {
    public:
        virtual ~IMprisService() = default;

        QString toString() const override
        {
            return "Mpris";
        }
    };
}
