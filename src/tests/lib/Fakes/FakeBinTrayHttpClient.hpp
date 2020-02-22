#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Updater/UpdateChannel.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeBinTrayHttpClient : public IHttpClient
    {
    public:
        void get(const QUrl &url) override;
        void get(const QUrl& url, const std::function<void(const QByteArray& replyData)>& callback) override;

        QString expectedVersion(UpdateChannel channel);
        QDate expectedDate(UpdateChannel channel);

    private:
        std::function<void(const QByteArray& replyData)> _callback;
    };

}
