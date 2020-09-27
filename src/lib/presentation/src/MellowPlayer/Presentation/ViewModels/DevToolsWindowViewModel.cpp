#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>

using namespace MellowPlayer::Presentation;

DevToolsWindowViewModel::DevToolsWindowViewModel(IQmlSingletons& qmlSingletons) : QmlSingleton("DevToolsWindow", this, qmlSingletons)
{
}
