#pragma once

#include <MellowPlayer/Infrastructure/Updater/ILatestRelease.hpp>

class QJsonArray;

namespace MellowPlayer::Infrastructure
{
    class IHttpClient;

    class LatestBinTrayRelease : public ILatestRelease
    {
    public:
        explicit LatestBinTrayRelease(IHttpClient& httpClient);

        void setChannel(UpdateChannel channel) override;
        void get() override;

    private:
        void onReplyReceived(const QByteArray& replyData);
        Release* parse(const QByteArray& reply);
        QString findLatestVersion(const QJsonArray& replyData);

        QString channelToString() const;
        IHttpClient& _httpClient;
        UpdateChannel _channel;

        QString makeUrl(QString path);
    };
}
