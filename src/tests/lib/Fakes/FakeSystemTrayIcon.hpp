#pragma once

#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>

namespace MellowPlayer::Presentation
{
    struct SystemTrayIconMessage
    {
        QString title;
        QString message;

        SystemTrayIconMessage(const QString& title, const QString& message) : title(title), message(message)
        {

        }

        bool operator==(const SystemTrayIconMessage& rhs) const
        {
            return title == rhs.title && message == rhs.message;
        }

        bool operator!=(const SystemTrayIconMessage& rhs) const
        {
            return !(rhs == *this);
        }
    };

    class FakeSystemTrayIcon : public ISystemTrayIcon
    {
    public:
        void show() override
        {
            _visible = true;
        }

        void hide() override
        {
            _visible = false;
        }

        bool isVisible() const { return _visible; }

        void showMessage(const QString& title, const QString& message) override
        {
            _messages.append({title, message});
        }

        QList<SystemTrayIconMessage> messages()
        {
            return _messages;
        }

        void setupFavoritesMenu() override
        {

        }

    private:
        bool _visible = false;
        QList<SystemTrayIconMessage> _messages;
    };
}