#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>
#include <QApplication>
#include <QTranslator>

namespace MellowPlayer::Presentation
{
    class MainWindowViewModel;
    class SettingsViewModel;

    class ApplicationViewModel : public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(QString buildInfo READ buildInfo CONSTANT)
        Q_PROPERTY(SettingsViewModel* settings READ settings CONSTANT)
    public:
        ApplicationViewModel(Infrastructure::IApplication& application,
                             Infrastructure::IQtApplication& qtApplication,
                             MainWindowViewModel& mainWindow,
                             SettingsViewModel& settingsViewModel);

        Q_INVOKABLE void quit();
        Q_INVOKABLE void restart();
        Q_INVOKABLE void showLogs();
        Q_INVOKABLE void clearCache();
        Q_INVOKABLE void clearCookies();

        SettingsViewModel* settings();

        // TODO should move into AboutWindowViewModel
        QString buildInfo() const;

    private:
        Infrastructure::IApplication& _application;
        Infrastructure::IQtApplication& _qtApplication;
        MainWindowViewModel& _mainWindow;
        SettingsViewModel& _settingsViewModel;
        QTranslator _translator;
        bool _restartRequested;
    };
}
