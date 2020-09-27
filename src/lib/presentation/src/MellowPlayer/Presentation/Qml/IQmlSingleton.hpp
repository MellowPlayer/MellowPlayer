#pragma once

#include "IQmlApplicationEngine.hpp"
#include <QString>

class QObject;

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    /**
     * Represents a qml singleton. If added to IQmlSingletons, it will be automatically registered in
     * the qml context as qml singleton instance.
     */
    class IQmlSingleton
    {
    public:
        virtual ~IQmlSingleton() = default;

        /**
         * Register the singleton to qml
         *
         * @param qmlApplicationEngine
         */
        virtual void registerTo(IQmlApplicationEngine& qmlApplicationEngine) = 0;
    };
}
