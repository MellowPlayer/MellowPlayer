#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>

using namespace MellowPlayer::Infrastructure;

class FakeHttpClient : public IHttpClient
{
public:
    void get(const QUrl& url) override;
    void get(const QUrl& url, const std::function<void(const QByteArray& replyData)>& callback) override;
};
