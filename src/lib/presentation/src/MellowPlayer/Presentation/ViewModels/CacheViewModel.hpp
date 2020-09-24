#pragma once

#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class CacheViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        explicit CacheViewModel(IContextProperties& contextProperties);

        Q_INVOKABLE void clear();
    };
}
