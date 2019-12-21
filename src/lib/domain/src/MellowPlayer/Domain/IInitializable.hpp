#pragma once

#include <QObject>
#include <QtCore/QString>
#include <functional>

namespace MellowPlayer::Domain
{
    class IInitializable : public QObject
    {
        Q_OBJECT
    public:
        using ResultCallback = std::function<void(bool)>;

        virtual void initialize(const ResultCallback& resultCallback) = 0;
        virtual void cleanUp(){};

        virtual QString errorMessage() const
        {
            return "No error";
        };
        virtual QString toString() const = 0;
    };
}
