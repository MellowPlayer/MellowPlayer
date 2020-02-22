#pragma once
#include <Fakes/FakeHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Network/IHttpClientFactory.hpp>

using namespace MellowPlayer::Infrastructure;

class FakeHttpClientFactory : public IHttpClientFactory
{
public:
    std::unique_ptr<IHttpClient> create() const override;
};

