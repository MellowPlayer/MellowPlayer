#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IQtApplication;
    class ApplicationNetworkProxy;

    class Application : public Infrastructure::IApplication
    {
        Q_OBJECT
    public:
        Application(IQtApplication& qtApplication, const std::shared_ptr<ApplicationNetworkProxy>& applicationNetworkProxy = nullptr);

        void initialize() override;
        int run() override;
        void quit(int returnCode = 0) override;
        void restart() override;
        void restoreWindow() override;

    private:
        Infrastructure::IQtApplication& _qtApp;
        std::shared_ptr<ApplicationNetworkProxy> _applicationNetworkProxy;
        bool _restartRequested;
    };
}
