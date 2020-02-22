#include "HttpClientFactory.hpp"
#include <MellowPlayer/Infrastructure/Network/HttpClient.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

unique_ptr<IHttpClient> HttpClientFactory::create() const
{
    return std::make_unique<HttpClient>();
}
