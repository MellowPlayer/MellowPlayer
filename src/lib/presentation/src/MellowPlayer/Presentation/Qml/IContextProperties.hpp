#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class IContextProperty;

    /**
     * Registers context properties in the current QmlContext.
     */
    class IContextProperties
    {
    public:
        virtual ~IContextProperties() = default;

        /**
         * Add a context property to the QML context.
         *
         * @param contextProperty
         */
        virtual void add(IContextProperty& contextProperty) = 0;
        virtual void registerToQml() = 0;
    };
}
