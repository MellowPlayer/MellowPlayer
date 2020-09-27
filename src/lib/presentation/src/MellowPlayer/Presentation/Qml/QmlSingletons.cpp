#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlSingleton.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingletons.hpp>
#include <QtQml>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

QmlSingletons::QmlSingletons(IQmlApplicationEngine& qmlApplicationEngine, IPlayer& player)
        : _qmlApplicationEngine(qmlApplicationEngine), _player(player)
{
}

void QmlSingletons::add(IQmlSingleton& qmlSingleton)
{
    _qmlSingletons.append(&qmlSingleton);
}

void QmlSingletons::registerToQml()
{
    _qmlApplicationEngine.registerSingletonInstance("Player", &_player);

    for (auto* qmlSingleton : _qmlSingletons)
        qmlSingleton->registerTo(_qmlApplicationEngine);
}
