#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>
#include <QString>

namespace MellowPlayer::Presentation
{
    class ISystemTrayIcon : public Domain::IInitializable
    {
    public:
        virtual ~ISystemTrayIcon() = default;

        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void showMessage(const QString& title, const QString& message) = 0;
    };
}
