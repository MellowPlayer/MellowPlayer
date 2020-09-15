#include "SingleInstanceCheckup.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QTimer>

#if defined(Q_OS_WIN)
#include <QLibrary>
#include <qt_windows.h>
using PProcessIdToSessionId = BOOL (WINAPI*)(DWORD, DWORD*);
static PProcessIdToSessionId pProcessIdToSessionId = 0;
#endif
#if defined(Q_OS_UNIX)
#include <ctime>
#include <unistd.h>
#endif

using namespace std;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Domain;

const QString SingleInstanceCheckup::_playPauseAction = "play-pause";
const QString SingleInstanceCheckup::_nextAction = "next";
const QString SingleInstanceCheckup::_previousAction = "previous";
const QString SingleInstanceCheckup::_restoreWindowAction = "restore-window";
const QString SingleInstanceCheckup::_toggleFavoriteAction = "toggle-favorite";

QString SingleInstanceCheckup::appSessionId(const QString &appId)
{
    QByteArray idc = appId.toUtf8();
    quint16 idNum = qChecksum(idc.constData(), idc.size());
    //### could do: two 16bit checksums over separate halves of id, for a 32bit result - improved uniqeness probability. Every-other-char split would be best.

    QString res = QLatin1String("mellowplayer-")
                  + QString::number(idNum, 16);
#if defined(Q_OS_WIN)
    if (!pProcessIdToSessionId) {
        QLibrary lib(QLatin1String("kernel32"));
        pProcessIdToSessionId = (PProcessIdToSessionId)lib.resolve("ProcessIdToSessionId");
    }
    if (pProcessIdToSessionId) {
        DWORD sessionId = 0;
        pProcessIdToSessionId(GetCurrentProcessId(), &sessionId);
        res += QLatin1Char('-') + QString::number(sessionId, 16);
    }
#else
    res += QLatin1Char('-') + QString::number(::getuid(), 16);
#endif
    return res;
}

SingleInstanceCheckup::SingleInstanceCheckup(IApplication& application,
                                         IPlayer& currentPlayer,
                                         ICommandLineArguments& commandLineArguments,
                                         ILocalServerFactory& localServerFactory,
                                         ILocalSocketFactory& localSocketFactory)
        : _logger(Loggers::logger("SingleInstanceCheckup")),
          _application(application),
          _currentPlayer(currentPlayer),
          _commandLineArguments(commandLineArguments),
          _localServerFactory(localServerFactory),
          _localSocketFactory(localSocketFactory),
          _lockFilePath(GetLockFilePath()),
          _isPrimary(false)
{
    auto lockFileDirectory = QFileInfo(_lockFilePath).dir().path();
    QDir().mkpath(lockFileDirectory);

    _lockFile.setFileName(_lockFilePath);
    _lockFile.open(QIODevice::ReadWrite);
}

void SingleInstanceCheckup::initialize(const ResultCallback& resultCallback)
{
    _resultCallback = resultCallback;

    LOG_INFO(_logger, "Lock file: " << _lockFilePath)
    if (isClient())
        initializeSecondaryApplication();
    else
        initializePrimaryApplication();
}

QString SingleInstanceCheckup::errorMessage() const
{
    return "Another instance is already running";
}

void SingleInstanceCheckup::initializePrimaryApplication()
{
    LOG_DEBUG(_logger, "Initializing primary application");

    _localServer = _localServerFactory.create(qApp->applicationName());
    connect(_localServer.get(), &ILocalServer::newConnection, this, &SingleInstanceCheckup::onSecondaryApplicationConnected);
    _localServer->listen();
    _isPrimary = true;

    _resultCallback(true);
}

void SingleInstanceCheckup::onSecondaryApplicationConnected()
{
    auto nextConnection = _localServer->nextPendingConnection();
    if (nextConnection)
    {
        if (_localSocket)
            _localSocket->disconnectFromServer();

        LOG_DEBUG(_logger, "Another application was started, showing this one instead");
        _localSocket = move(nextConnection);
        connect(_localSocket.get(), &ILocalSocket::readyRead, this, &SingleInstanceCheckup::onSecondaryApplicationActionRequest);
    }
}

void SingleInstanceCheckup::onSecondaryApplicationActionRequest()
{
    QString action = QString(_localSocket->readAll()).split("\n")[0];
    LOG_DEBUG(_logger, "Secondary application request: " << action);

    if (action == _playPauseAction)
        _currentPlayer.togglePlayPause();
    else if (action == _nextAction)
        _currentPlayer.next();
    else if (action == _previousAction)
        _currentPlayer.previous();
    else if (action == _toggleFavoriteAction)
        _currentPlayer.toggleFavoriteSong();
    else
        _application.restoreWindow();
}

void SingleInstanceCheckup::initializeSecondaryApplication()
{
    LOG_DEBUG(_logger, "Initializing secondary application");
    _isPrimary = false;
    LOG_DEBUG(_logger, "Another instance is already running, transmitting command line arguments...");

    _localSocket = _localSocketFactory.create();
    connect(_localSocket.get(), &ILocalSocket::connected, this, &SingleInstanceCheckup::onConnectedToPrimaryApplication);
    connect(_localSocket.get(), &ILocalSocket::error, this, &SingleInstanceCheckup::onConnectionErrorWithPrimaryApplication);
    _localSocket->connectToServer(qApp->applicationName(), QIODevice::WriteOnly);
}

void SingleInstanceCheckup::onConnectedToPrimaryApplication()
{
    LOG_DEBUG(_logger, "connection with the primary application succeeded");
    QString action = requestedAcion();
    LOG_DEBUG(_logger, "sending action: " << action);
    _localSocket->write(action + "\n");
    _resultCallback(false);
}

void SingleInstanceCheckup::onConnectionErrorWithPrimaryApplication()
{
    LOG_WARN(_logger, "could not connect to the primary application, quitting...");
    _resultCallback(false);
}

QString SingleInstanceCheckup::requestedAcion() const
{
    if (_commandLineArguments.playPauseRequested())
        return _playPauseAction;
    else if (_commandLineArguments.nextRequested())
        return _nextAction;
    else if (_commandLineArguments.previousRequested())
        return _previousAction;
    else if (_commandLineArguments.toggleFavoriteRequested())
        return _toggleFavoriteAction;
    return _restoreWindowAction;
}

void SingleInstanceCheckup::cleanUp()
{
    if (_isPrimary)
    {
        _localServer->close();
        _lockFile.unlock();
    }
    else
    {
        _localSocket->disconnectFromServer();
    }
}

bool SingleInstanceCheckup::IsAnotherInstanceRunning()
{
    QLockFile lock(GetLockFilePath());
    lock.setStaleLockTime(0);
    if (lock.tryLock(100)) {
        lock.unlock();
        return false;
    }
    return true;
}

QString SingleInstanceCheckup::GetLockFilePath()
{
    return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first() + QDir::separator() + "single-instance.lock";
}

bool SingleInstanceCheckup::isEnabled() const
{
    return !_commandLineArguments.allowMultipleInstances();
}

bool SingleInstanceCheckup::isClient()
{
    if (_lockFile.isLocked())
        return false;

    if (!_lockFile.lock(QtLockedFile::WriteLock, false))
        return true;

    return false;
}
