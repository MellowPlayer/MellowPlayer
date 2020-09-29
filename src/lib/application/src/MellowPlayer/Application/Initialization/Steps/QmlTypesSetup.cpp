#include "QmlTypesSetup.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

QmlTypesSetup::QmlTypesSetup(MellowPlayerQmlPlugin& qmlPlugin, IQmlSingletons& qmlSingletons) : _qmlPlugin(qmlPlugin), _qmlSingletons(qmlSingletons)
{
}

void QmlTypesSetup::initialize(const ResultCallback& resultCallback)
{
    _qmlPlugin.registerTypes("MellowPlayer");
    _qmlPlugin.initializeEngine(nullptr, "MellowPlayer");
    resultCallback(true);
}
