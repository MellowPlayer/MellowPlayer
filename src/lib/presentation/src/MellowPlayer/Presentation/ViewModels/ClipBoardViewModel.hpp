#pragma once

#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class ClipBoardViewModel : public QObject, public QmlSingleton
    {
        Q_OBJECT
    public:
        explicit ClipBoardViewModel(IQmlSingletons& qmlSingletons);

        Q_INVOKABLE void setText(const QString& text);
        Q_INVOKABLE bool canPaste() const;

    signals:
        void textCopied(const QString& text);
    };
}
