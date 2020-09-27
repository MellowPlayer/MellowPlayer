#pragma once

#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class DevToolsWindowViewModel : public QObject, public QmlSingleton
    {
        Q_OBJECT
    public:
        DevToolsWindowViewModel(IQmlSingletons& qmlSingletons);

    signals:
        void show();
    };
}
