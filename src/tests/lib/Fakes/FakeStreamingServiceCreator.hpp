#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>

namespace MellowPlayer::Domain
{
    class FakeStreamingServiceCreator : public IStreamingServiceCreator
    {
    public:
        QString create(const QString& serviceName,
                       const QString& serviceUrl,
                       const QString& authorName,
                       const QString& authorWebsite,
                       const QString& supportedPlatforms) override
        {
            Q_UNUSED(serviceName)
            Q_UNUSED(serviceUrl)
            Q_UNUSED(authorName)
            Q_UNUSED(authorWebsite)
            Q_UNUSED(supportedPlatforms)

            _count++;

            return "/tmp/pluginDir";
        }

        int count()
        {
            return _count;
        }

    private:
        int _count = 0;
    };
}
