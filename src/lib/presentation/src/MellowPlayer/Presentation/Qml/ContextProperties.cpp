#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperty.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <QtQml/QtQml>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ContextProperties::ContextProperties(IQmlApplicationEngine& qmlApplicationEngine, IPlayer& player)
        : _qmlApplicationEngine(qmlApplicationEngine), _player(player)
{
}

void ContextProperties::add(IContextProperty& contextProperty)
{
    _contextProperties.append(&contextProperty);
}

void ContextProperties::initialize(const ResultCallback& resultCallback)
{
    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    _qmlApplicationEngine.setContextProperty("_player", &_player);

    for (auto* contextProperty : _contextProperties)
        contextProperty->initialize(_qmlApplicationEngine);

    resultCallback(true);
}
