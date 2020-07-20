#pragma once

#include <MellowPlayer/Infrastructure/AdBlock/IHttpBlockListLoader.hpp>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IHttpClient;

    class HttpBlockListLoader : public IHttpBlockListLoader
    {
        Q_OBJECT
    public:
        explicit HttpBlockListLoader(std::unique_ptr<IHttpClient> httpClient);

        void load(QString source, const std::function<void (QList<QString>)>) const override;

    private:
        std::unique_ptr<IHttpClient> _httpClient;
    };
}
