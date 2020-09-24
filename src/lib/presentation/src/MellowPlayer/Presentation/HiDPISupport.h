#pragma once

#include <QString>

namespace MellowPlayer::Domain
{
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class HiDPISupport
    {
    public:
        HiDPISupport(const QString& organizationName="MellowPlayer");

        void configure();

    private:
        QString _organizationName;
    };
}
