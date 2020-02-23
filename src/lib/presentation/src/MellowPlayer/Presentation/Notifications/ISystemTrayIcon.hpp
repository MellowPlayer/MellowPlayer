#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <QString>

namespace MellowPlayer::Presentation
{
    class ISystemTrayIcon : public QObject
    {
    public:
        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void showMessage(const QString& title, const QString& message) = 0;
        virtual void setupFavoritesMenu() = 0;
    };
}
