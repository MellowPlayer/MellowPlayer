#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Presentation/AdBlock/AdBlockRequestInterceptor.hpp>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IFileBlockListLoader;
    class IHttpBlockListLoader;
}

namespace MellowPlayer::Application
{
    class AdBlockSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit AdBlockSetup(std::unique_ptr<Presentation::IAdBlockRequestInterceptor> interceptor,
                              Infrastructure::IFileBlockListLoader& fileLoader,
                              Infrastructure::IHttpBlockListLoader& httpLoader);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        std::unique_ptr<Presentation::IAdBlockRequestInterceptor> _interceptor;
        Infrastructure::IFileBlockListLoader& _fileLoader;
        Infrastructure::IHttpBlockListLoader& _httpLoader;
    };
}
