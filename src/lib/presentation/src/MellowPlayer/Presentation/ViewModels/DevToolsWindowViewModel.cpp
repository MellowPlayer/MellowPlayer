#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>

using namespace MellowPlayer::Presentation;

DevToolsWindowViewModel::DevToolsWindowViewModel(std::shared_ptr<IContextProperties> contextProperties) : ContextProperty("devTools", this, contextProperties)
{
}
