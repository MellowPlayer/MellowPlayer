#pragma once

#include <MellowPlayer/Domain/Initializable.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QString>
#include <QTimer>
#include <QLockFile>
#include <MellowPlayer/Infrastructure/LockedFiled/qtlockedfile.hpp>

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
                              Infrastructure::ILocalServerFactory& localServerFactory,
                              Infrastructure::ILocalSocketFactory& localSocketFactory);

        void initialize(const ResultCallback& resultCallback) override;
        void cleanUp() override;
        bool isEnabled() const override;

        QString errorMessage() const override;

        static bool IsAnotherInstanceRunning();

    private:
        static QString GetLockFilePath();
        void initializePrimaryApplication();
        void onSecondaryApplicationConnected();
        void onSecondaryApplicationActionRequest();
        QString appSessionId(const QString &appId);
        bool isClient();

        void initializeSecondaryApplication();
        void onConnectedToPrimaryApplication();
        void onConnectionErrorWithPrimaryApplication();
        QString requestedAcion() const;

        Domain::ILogger& _logger;
        Infrastructure::IApplication& _application;
        Domain::IPlayer& _currentPlayer;
        Infrastructure::ICommandLineArguments& _commandLineArguments;
        Infrastructure::ILocalServerFactory& _localServerFactory;
        Infrastructure::ILocalSocketFactory& _localSocketFactory;
        std::shared_ptr<Infrastructure::ILocalServer> _localServer;
        std::shared_ptr<Infrastructure::ILocalSocket> _localSocket;
        QString _lockFilePath;
        Infrastructure::QtLockedFile _lockFile;
        bool _isPrimary;
        ResultCallback _resultCallback;

        static const QString _playPauseAction;
        static const QString _nextAction;
        static const QString _previousAction;
        static const QString _restoreWindowAction;
        static const QString _toggleFavoriteAction;
    };
}
