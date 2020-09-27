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
    class QmlSingleton : public QObject, public IQmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(QObject* instance READ instance CONSTANT)
    public:
        /**
         * Constructor that adds the property to the qml context.
         *
         * @param instance
         */
        QmlSingleton(const QString& name, QObject* instance);

        QObject* instance();

        virtual void registerTo(IQmlApplicationEngine& qmlApplicationEngine) override;

    private:
        QString _name;
        QObject* _instance;
    };
}
