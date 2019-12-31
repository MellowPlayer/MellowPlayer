#pragma once

#include <MellowPlayer/Domain/IInitializable.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Qml/IContextProperties.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>

namespace MellowPlayer::Presentation
{
    class GuiSetup : public Domain::IInitializable
    {
        Q_OBJECT
    public:
        GuiSetup(ApplicationViewModel& application,
                 IMainWindow& mainWindow,
                 SettingsViewModel& settings,
                 ThemeViewModel& theme,
                 UpdaterViewModel& updater,
                 ListeningHistoryViewModel& listeningHistory,
                 StreamingServicesViewModel& streamingServices,
                 IContextProperties& contextProperties,
                 ZoomViewModel& zoomViewModel,
                 Infrastructure::ICommandLineArguments& commandLineOptions);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;
        QString toString() const override;

    private:
        ApplicationViewModel& _application;
        IMainWindow& _mainWindow;
        UpdaterViewModel& _updater;
        ListeningHistoryViewModel& _listeningHistory;
        StreamingServicesViewModel& _streamingServices;
        CacheViewModel _cache;
        CookiesViewModel _cookies;
        ClipBoardViewModel _clipboard;
        DevToolsWindowViewModel _devToolsWindow;
        ZoomViewModel& _zoomViewModel;
        Infrastructure::ICommandLineArguments& _commandLineArguments;
        QTranslator _translator;
        IContextProperties& _contextProperties;
    };
}
