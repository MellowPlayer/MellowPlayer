#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/IQmlSingletons.hpp>
#include <MellowPlayer/Presentation/ViewModels/ActiveThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/RemoteControlViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>

namespace MellowPlayer::Application
{
    class QmlTypesSetup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        QmlTypesSetup(Presentation::ApplicationViewModel&,
                      Presentation::SettingsViewModel&,
                      Presentation::UpdaterViewModel&,
                      Presentation::ListeningHistoryViewModel&,
                      Presentation::ZoomViewModel&,
                      Presentation::RemoteControlViewModel&,
                      Presentation::IQmlSingletons& qmlSingletons);

        void initialize(const ResultCallback& resultCallback) override;

    private:
        Presentation::ClipBoardViewModel _clipBoardViewModel;
        Presentation::DevToolsWindowViewModel _devToolWindowViewModel;
        Presentation::IQmlSingletons& _qmlSingletons;
    };
}
