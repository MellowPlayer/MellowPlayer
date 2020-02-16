#pragma once

namespace MellowPlayer::Presentation
{
    struct Notification;

    class IPlayerNotifications
    {
    public:
        virtual ~IPlayerNotifications() = default;

        virtual void listen() = 0;
        virtual bool display(const Notification& notification) = 0;
    };
}
