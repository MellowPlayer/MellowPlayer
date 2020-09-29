#pragma once

#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class ClipBoardViewModel : public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(QString copiedText READ copiedText NOTIFY copiedTextChanged)
    public:
        ClipBoardViewModel();

        QString copiedText() const;
        Q_INVOKABLE void setText(const QString& text);
        Q_INVOKABLE bool canPaste() const;

    signals:
        void copiedTextChanged();

    private:
        QString _copiedText;
    };
}
