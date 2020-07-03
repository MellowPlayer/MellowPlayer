#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Presentation/AdBlock/AdBlockRequestInterceptor.hpp>
#include <QWebEngineProfile>
#include <memory>

namespace MellowPlayer::Application {
    class AdBlockSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit AdBlockSetup(std::unique_ptr<Presentation::AdBlockRequestInterceptor> interceptor);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        QWebEngineProfile* _profile;
        std::unique_ptr<Presentation::AdBlockRequestInterceptor> _interceptor;
    };
}
