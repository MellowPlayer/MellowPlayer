#pragma once

#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QtCore/QObject>

namespace MellowPlayer::Presentation
{
    class CacheViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        explicit CacheViewModel(std::shared_ptr<IContextProperties> contextProperties);

        Q_INVOKABLE void clear();
    };
}
