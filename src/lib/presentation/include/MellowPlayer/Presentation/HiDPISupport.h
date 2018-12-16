#pragma once

namespace MellowPlayer::Domain
{
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class HiDPISupport
    {
    public:
        HiDPISupport(Domain::Settings& settings);

        void configure();

    private:
        Domain::Settings& _settings;
    };
}
