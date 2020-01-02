#include "StreamingServicesSetup.hpp"
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


StreamingServicesSetup::StreamingServicesSetup(StreamingServicesViewModel& streamingServices) : _streamingServices(streamingServices)
{

}

void StreamingServicesSetup::initialize(const ResultCallback& resultCallback)
{
    _streamingServices.initialize();
    resultCallback(true);
}
