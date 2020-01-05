#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/RemoteControlViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>

namespace MellowPlayer::Application
{
    class QmlTypesSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        QmlTypesSetup(Presentation::ApplicationViewModel&,
                      Presentation::IMainWindow&,
                      Presentation::SettingsViewModel&,
                      Presentation::ThemeViewModel&,
                      Presentation::UpdaterViewModel&,
                      Presentation::ListeningHistoryViewModel&,
                      Presentation::StreamingServicesViewModel&,
                      Presentation::ZoomViewModel&,
                      Presentation::CacheViewModel&,
                      Presentation::CookiesViewModel&,
                      Presentation::ClipBoardViewModel&,
                      Presentation::DevToolsWindowViewModel&,
                      Presentation::RemoteControlViewModel&,
                      Presentation::IContextProperties& contextProperties);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::IContextProperties& _contextProperties;
    };
}
