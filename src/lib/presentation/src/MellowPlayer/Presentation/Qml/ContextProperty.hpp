#pragma once

#include "IContextProperty.hpp"
#include <memory>

namespace MellowPlayer::Presentation
{
    class IContextProperties;

    /**
     * All context properties should inherit from this intermediary base class in order to be added automatically
     * to the application's QML context.
     */
    class ContextProperty : public IContextProperty
    {
    public:
        /**
         * Constructor that adds the property to the qml context.
         *
         * @param contextProperties
         */
        ContextProperty(const QString& name, QObject* propertyObject, IContextProperties& contextProperties);

        virtual void initialize(IQmlApplicationEngine& qmlApplicationEngine) override;

    private:
        QString _name;
        QObject* _propertyObject;
    };
}
