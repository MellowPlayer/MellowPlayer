#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClientFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class HttpClientFactory : public IHttpClientFactory
    {
    public:
        std::unique_ptr<IHttpClient> create() const override;
    };
}
