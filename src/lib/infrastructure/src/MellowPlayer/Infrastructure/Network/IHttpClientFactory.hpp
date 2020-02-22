#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IHttpClientFactory : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IHttpClientFactory() = default;

        virtual std::unique_ptr<IHttpClient> create() const = 0;
    };
}