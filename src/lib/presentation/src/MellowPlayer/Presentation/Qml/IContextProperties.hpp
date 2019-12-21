#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>

namespace MellowPlayer::Presentation
{
    class IContextProperty;

    /**
     * Registers context properties in the current QmlContext.
     */
    class IContextProperties : public Domain::IInitializable
    {
    public:
        virtual ~IContextProperties() = default;

        /**
         * Add a context property to the QML context.
         *
         * @param contextProperty
         */
        virtual void add(IContextProperty& contextProperty) = 0;

        QString toString() const override
        {
            return "ContextProperties";
        }
    };
}
