#include "ListeningHistorySetup.hpp"
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


ListeningHistorySetup::ListeningHistorySetup(ListeningHistoryViewModel& listeningHistory) : _listeningHistory(listeningHistory)
{

}

void ListeningHistorySetup::initialize(const ResultCallback& resultCallback)
{
    _listeningHistory.load();
    resultCallback(true);
}
