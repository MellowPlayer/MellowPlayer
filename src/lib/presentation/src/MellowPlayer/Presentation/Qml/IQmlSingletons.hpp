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

        virtual void registerToQml() = 0;

        static IQmlSingletons* instance();

    protected:
        static IQmlSingletons* _instance;
    };
}
