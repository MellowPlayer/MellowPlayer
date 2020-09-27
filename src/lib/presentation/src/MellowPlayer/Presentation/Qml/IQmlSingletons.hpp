#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class IQmlSingleton;

    /**
     * Registers qml singletons for use in QML.
     */
    class IQmlSingletons
    {
    public:
        virtual ~IQmlSingletons() = default;

        /**
         * Add a qml singleton for use in QML
         *
         * @param qmlSingleton
         */
        virtual void add(IQmlSingleton& qmlSingleton) = 0;
        virtual void registerToQml() = 0;
    };
}
