#include "FakeHttpClient.hpp"
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <Utils/Helpers.hpp>

void FakeHttpClient::get(const QUrl&)
{
    emit replyReceived(getValidReplyData());
}

void FakeHttpClient::get(const QUrl&, const std::function<void(const QByteArray& replyData)>& callback)
{
    callback("");
}
