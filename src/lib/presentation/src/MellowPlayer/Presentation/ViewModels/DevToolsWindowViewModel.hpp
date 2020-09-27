#pragma once

#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class DevToolsWindowViewModel : public QmlSingleton
    {
        Q_OBJECT
    public:
        DevToolsWindowViewModel();

    signals:
        void show();
    };
}
