#pragma once

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
    public:
        MainWindowViewModel(Domain::ISettingsStore& settingsStore);

        // IMainWindow implementation
        void show() override;
        void hide() override;
        void raise() override;

        // Properties for QML
        bool isVisible() const;
        ZoomViewModel* zoom();

        Q_INVOKABLE void requestQuit() override;

    signals:
        void quitRequest();

    public slots:
        void setVisible(bool visible);

    signals:
        void visibleChanged();
        void raiseRequested();

    private:
        bool _visible;
        Domain::ILogger& _logger;
        ZoomViewModel _zoom;
    };
}
