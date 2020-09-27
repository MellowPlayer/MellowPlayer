#pragma once

#include "IQmlSingleton.hpp"
#include <memory>

namespace MellowPlayer::Presentation
{
    class IQmlSingletons;

    /**
     * All qml singleton should inherit from this intermediary base class in order to be added automatically
     * to the application's QML context.
     */
    class QmlSingleton : public IQmlSingleton
    {
    public:
        /**
         * Constructor that adds the property to the qml context.
         *
         * @param instance
         */
        QmlSingleton(const QString& name, QObject* propertyObject, IQmlSingletons& instance);

        virtual void registerTo(IQmlApplicationEngine& qmlApplicationEngine) override;

    private:
        QString _name;
        QObject* _instance;
    };
}
