#include "AdBlockSetup.hpp"

using namespace MellowPlayer::Application;

AdBlockSetup::AdBlockSetup(std::unique_ptr<Presentation::AdBlockRequestInterceptor> interceptor)
    : _profile(QWebEngineProfile::defaultProfile()),
      _interceptor(std::move(interceptor))
{
}

void AdBlockSetup::initialize(const ResultCallback &resultCallback)
{
    _profile->setRequestInterceptor(_interceptor.get());
    resultCallback(true);
}
