#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Updater/UpdateChannel.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeBinTrayHttpClient : public IHttpClient
    {
    public:
        void get(const QString &url) override;

        QString expectedVersion(UpdateChannel channel);
        QDate expectedDate(UpdateChannel channel);
    };

}
