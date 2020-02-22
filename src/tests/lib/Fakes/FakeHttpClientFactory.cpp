#include "FakeHttpClientFactory.hpp"
#include <Fakes/FakeHttpClient.hpp>

std::unique_ptr<IHttpClient> FakeHttpClientFactory::create() const
{
    return std::make_unique<FakeHttpClient>();
}
