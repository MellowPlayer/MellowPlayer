#pragma once

#include <MellowPlayer/Infrastructure/Updater/ILatestRelease.hpp>
#include <memory>

class QJsonArray;

namespace MellowPlayer::Infrastructure
{
    class IHttpClient;

    class LatestBinTrayRelease : public ILatestRelease
    {
    public:
        explicit LatestBinTrayRelease(std::unique_ptr<IHttpClient> httpClient);

        void setChannel(UpdateChannel channel) override;
        void get() override;

    private:
        void onReplyReceived(const QByteArray& replyData);
        Release* parse(const QByteArray& reply);
        QString findLatestVersion(const QJsonArray& replyData);

        QString channelToString() const;
        std::unique_ptr<IHttpClient> _httpClient;
        UpdateChannel _channel;

        QString makeUrl(QString path);
    };
}
