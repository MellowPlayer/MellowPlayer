#include <MellowPlayer/Presentation/Mpris/NullMprisService.hpp>

bool MellowPlayer::Presentation::NullMprisService::start()
{
    return true;
}
void MellowPlayer::Presentation::NullMprisService::initialize(const ResultCallback& resultCallback)
{
    resultCallback(true);
}
