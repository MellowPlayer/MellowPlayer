#include "HttpBlockListLoader.hpp"
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <QUrl>
#include <QByteArray>

using namespace MellowPlayer::Infrastructure;

HttpBlockListLoader::HttpBlockListLoader(std::unique_ptr<IHttpClient> httpClient)
    : _httpClient(std::move(httpClient))
{
}

void HttpBlockListLoader::load(QString source, const std::function<void (QList<QString>)> callback) const
{
    _httpClient->get(QUrl(source), [callback](const QByteArray& replyData) {
        QList<QString> blocklist;
        auto content = QString::fromUtf8(replyData);

        for (const auto &hostname : content.split('\n')) {
            // if line starts with '#' it is a comment
            if (hostname.isEmpty() || hostname.startsWith("#"))
                continue;
            blocklist.append(hostname);
        }
        callback(blocklist);
    });
}
