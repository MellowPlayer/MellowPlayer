#pragma once

#include "RunningServicesViewModel.hpp"
#include <MellowPlayer/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <MellowPlayer/Presentation/ViewModels/ZoomViewModel.hpp>
#include <QObject>

namespace MellowPlayer::Domain
{
    class ILogger;
    class ISettingsStore;
}

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    class MainWindowViewModel : public IMainWindow
    {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
        Q_PROPERTY(ZoomViewModel* zoom READ zoom CONSTANT)
        Q_PROPERTY(bool fullScreen READ isFullScreen WRITE setFullScreen NOTIFY fullScreenChanged)
        Q_PROPERTY(RunningServicesViewModel* runningServices READ runningServices CONSTANT)
    public:
        MainWindowViewModel(Domain::ISettingsStore& settingsStore,
                            RunningServicesViewModel& runningServicesViewModel);

        // IMainWindow implementation
        void show() override;
        void hide() override;
        void raise() override;

        // Properties for QML
        bool isVisible() const;
        ZoomViewModel* zoom();

        Q_INVOKABLE void requestQuit() override;

        RunningServicesViewModel* runningServices();
        bool isFullScreen() const;

    signals:
        void quitRequest();
        void visibleChanged();
        void raiseRequested();
        void fullScreenChanged();
        void forceQuitRequest();

    public slots:
        void setVisible(bool visible);
        void setFullScreen(bool value);

    private:
        bool _visible;
        Domain::ILogger& _logger;
        ZoomViewModel _zoom;
        RunningServicesViewModel& _runningServices;
        bool _fullScreen = false;
    };
}
