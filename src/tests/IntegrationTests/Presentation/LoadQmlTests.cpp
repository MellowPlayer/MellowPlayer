#include "Utils/DependencyPool.hpp"
#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <Mocks/PlayerMock.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

TEST_CASE("LoadQmlTests")
{
    QmlApplicationEngine qmlApplicationEngine;
    auto playerMock = PlayerMock::get();
    auto contextProperties = std::make_shared<ContextProperties>(qmlApplicationEngine, playerMock.get());
    MainWindowViewModel mainWindow(*contextProperties, qmlApplicationEngine);
    contextProperties->registerToQml();

    REQUIRE_NOTHROW(mainWindow.load());
}
