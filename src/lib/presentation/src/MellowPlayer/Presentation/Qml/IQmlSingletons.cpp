#include "IQmlSingletons.hpp"

using namespace MellowPlayer::Presentation;

IQmlSingletons* IQmlSingletons::_instance = nullptr;

IQmlSingletons* IQmlSingletons::instance()
{
    return _instance;
}
