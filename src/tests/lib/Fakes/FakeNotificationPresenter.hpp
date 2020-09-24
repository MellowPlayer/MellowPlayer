#pragma once

#include <memory>
#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

namespace MellowPlayer::Presentation
{
    class FakeNotificationPresenter : public INotificationPresenter
    {
    public:
        void initialize() override
        {
        }

        bool display(const Notification& notification) override
        {
            _displayedNotifications.append(notification);
            return true;
        }

        void clearDisplayedNotifications()
        {
            _displayedNotifications.clear();
        }

        QList<Notification> displayedNotifications() const
        {
            return _displayedNotifications;
        }

    private:
        QList<Notification> _displayedNotifications;
    };
}