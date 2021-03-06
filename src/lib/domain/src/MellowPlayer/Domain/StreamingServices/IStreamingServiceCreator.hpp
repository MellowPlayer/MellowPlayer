#pragma once

#include <QString>

namespace MellowPlayer::Domain
{
    class IStreamingServiceCreator
    {
    public:
        virtual ~IStreamingServiceCreator() = default;

        virtual QString create(const QString& serviceName,
                               const QString& serviceUrl,
                               const QString& authorName,
                               const QString& authorWebsite,
                               const QString& supportedPlatforms) = 0;
    };
}
