#pragma once

#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class CookiesViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        explicit CookiesViewModel(IContextProperties& contextProperties);

        Q_INVOKABLE void clear();
    };
}
