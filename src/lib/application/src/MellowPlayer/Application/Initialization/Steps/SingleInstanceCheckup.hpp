#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QString>
#include <QTimer>
#include <QtCore/QLockFile>
#include <boost-di-extensions/Factory.hpp>

namespace MellowPlayer::Domain
{
    class ILogger;
    class IPlayer;
}

namespace MellowPlayer::Infrastructure
{
    class IQtApplication;
    class ICommandLineArguments;
    class IApplication;
}

namespace MellowPlayer::Application
{
    class SingleInstanceCheckup : public Domain::Initializable
    {
        Q_OBJECT
    public:
        SingleInstanceCheckup(Infrastructure::IApplication& application,
                              Domain::IPlayer& currentPlayer,
                              Infrastructure::ICommandLineArguments& commandLineArguments,
                              IFactory<Infrastructure::ILocalServer, QString>& localServerFactory,
                              IFactory<Infrastructure::ILocalSocket>& localSocketFactory);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;
        bool isEnabled() const override;

        QString errorMessage() const override;

        static bool IsAnotherInstanceRunning();

    private slots:
        void pollState();

    private:
        static QString GetLockFilePath();
        void initializePrimaryApplication();
        void onSecondaryApplicationConnected();
        void onSecondaryApplicationActionRequest();

        void initializeSecondaryApplication();
        void onConnectedToPrimaryApplication();
        void onConnectionErrorWithPrimaryApplication();
        QString requestedAcion() const;

        Domain::ILogger& _logger;
        Infrastructure::IApplication& _application;
        Domain::IPlayer& _currentPlayer;
        Infrastructure::ICommandLineArguments& _commandLineArguments;
        IFactory<Infrastructure::ILocalServer, QString>& _localServerFactory;
        IFactory<Infrastructure::ILocalSocket>& _localSocketFactory;
        std::unique_ptr<Infrastructure::ILocalServer> _localServer;
        std::unique_ptr<Infrastructure::ILocalSocket> _localSocket;
        QString _lockFilePath;
        QLockFile _lockFile;
        bool _isPrimary;
        QTimer _pollStateTimer;
        ResultCallback _resultCallback;

        static const QString _playPauseAction;
        static const QString _nextAction;
        static const QString _previousAction;
        static const QString _restoreWindowAction;
        static const QString _toggleFavoriteAction;
    };
}
