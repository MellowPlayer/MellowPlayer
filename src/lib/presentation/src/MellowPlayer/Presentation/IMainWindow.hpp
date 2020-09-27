#pragma once

#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class IMainWindow : public QmlSingleton
    {
        Q_OBJECT
    public:
        using QmlSingleton::QmlSingleton;

        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void raise() = 0;
        virtual void requestQuit() = 0;

    signals:
        void forceQuitRequest();
    };
}
