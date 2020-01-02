#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>

namespace MellowPlayer::Presentation
{
    class ISystemTrayIcon;
}

namespace MellowPlayer::Application
{
    class SystemTrayIconStartup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        explicit SystemTrayIconStartup(Presentation::ISystemTrayIcon& systemTrayIcon);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::ISystemTrayIcon& _systemTrayIcon;
    };
}
