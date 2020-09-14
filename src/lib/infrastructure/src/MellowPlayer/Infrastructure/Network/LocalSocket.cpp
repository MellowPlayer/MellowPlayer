#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>

using namespace MellowPlayer::Infrastructure;

LocalSocket::LocalSocket() : _qLocalSocket(new QLocalSocket(this))
{
    initSignals();
}

void LocalSocket::connectToServer(const QString& serverName, QIODevice::OpenMode openMode)
{
#ifndef Q_OS_WIN
    auto fullServerName = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first() + QDir::separator() + serverName;
    _qLocalSocket->connectToServer(fullServerName, openMode);
#else
    _qLocalSocket->connectToServer(serverName, openMode);
#endif
}

void LocalSocket::disconnectFromServer()
{
    _qLocalSocket->disconnectFromServer();
}

void LocalSocket::write(const QString& data)
{
    if (_qLocalSocket->state() == QLocalSocket::ConnectedState)
    {
        _qLocalSocket->write(data.toLocal8Bit());
        _qLocalSocket->waitForBytesWritten();
    }
    else
        throw std::logic_error("cannot write data on a socket that is not connected");
}

void LocalSocket::setQLocalSocket(QLocalSocket* localSocket)
{
    delete _qLocalSocket;
    _qLocalSocket = localSocket;
    initSignals();
}

QString LocalSocket::readAll()
{
    return _qLocalSocket->readAll();
}

void LocalSocket::initSignals()
{
    connect(_qLocalSocket, &QLocalSocket::connected, this, &LocalSocket::connected);
    connect(_qLocalSocket, &QLocalSocket::disconnected, this, &LocalSocket::disconnected);
    connect(_qLocalSocket, &QLocalSocket::readyRead, this, &LocalSocket::readyRead);
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(_qLocalSocket, &QLocalSocket::errorOccurred, [=](QLocalSocket::LocalSocketError) { emit error(); });
#else
    connect(_qLocalSocket, QNonConstOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error), [=](QLocalSocket::LocalSocketError) { emit error(); });
#endif
}

std::shared_ptr<ILocalSocket> LocalSocketFactory::create()
{
    return std::make_shared<LocalSocket>();
}
