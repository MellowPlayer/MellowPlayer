#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QApplication>
#include <QTranslator>

namespace MellowPlayer::Presentation
{
    class IMainWindow;

    class ApplicationViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
        Q_PROPERTY(QString buildInfo READ buildInfo CONSTANT)
    public:
        ApplicationViewModel(Infrastructure::IApplication& application,
                             Infrastructure::IQtApplication& qtApplication,
                             IMainWindow& mainWindow,
                             IContextProperties& contextProperties);

        Q_INVOKABLE void quit();
        Q_INVOKABLE void restart();
        Q_INVOKABLE void showLogs();

        QString buildInfo() const;

    private:
        Infrastructure::IApplication& _application;
        Infrastructure::IQtApplication& _qtApplication;
        IMainWindow& _mainWindow;
        QTranslator _translator;
        bool _restartRequested;
    };
}
