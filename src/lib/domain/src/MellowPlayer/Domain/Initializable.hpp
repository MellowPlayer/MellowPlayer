#pragma once

#include <QObject>
#include <QtCore/QString>
#include <functional>

namespace MellowPlayer::Domain
{
    class Initializable : public QObject
    {
        Q_OBJECT
    public:
        using ResultCallback = std::function<void(bool)>;

        virtual void initialize(const ResultCallback& resultCallback)
        {
            resultCallback(true);
        };

        virtual void cleanUp()
        {

        };

        virtual bool isEnabled() const
        {
            return true;
        }

        virtual QString errorMessage() const
        {
            return "";
        };

        virtual QString toString() const
        {
            return QString(metaObject()->className()).split(":").last();
        };
    };
}
