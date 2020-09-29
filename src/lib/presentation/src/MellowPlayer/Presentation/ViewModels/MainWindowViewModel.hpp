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
        Q_PROPERTY(QString currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
        Q_PROPERTY(QString selectServicePage READ selectServicePage CONSTANT)
        Q_PROPERTY(QString runningServicesPage READ runningServicesPage CONSTANT)
        Q_PROPERTY(bool isOnRunningServicesPage READ isOnRunningServicesPage NOTIFY currentPageChanged)
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

        QString currentPage() const;
        void setCurrentPage(const QString& pageName);

        QString selectServicePage() const;
        QString runningServicesPage() const;
        bool isOnRunningServicesPage() const;

        Q_INVOKABLE void toggleActivePage();
        Q_INVOKABLE void requestQuit() override;

        RunningServicesViewModel* runningServices();
        bool isFullScreen() const;

    signals:
        void quitRequest();
        void currentPageChanged();
        void visibleChanged();
        void raiseRequested();
        void fullScreenChanged();

    public slots:
        void setVisible(bool visible);
        void setFullScreen(bool value);

    private:
        bool _visible;
        Domain::ILogger& _logger;
        ZoomViewModel _zoom;
        RunningServicesViewModel& _runningServices;
        QString _currentPage{selectServicePage()};
        bool _fullScreen = false;
    };
}
