#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QDebug>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>

using namespace std;
using namespace MellowPlayer::Infrastructure;

LocalServer::LocalServer(ILocalSocketFactory& localSocketFactory, const QString& serverName) : _localSocketFactory(localSocketFactory), _serverName(serverName)
{
    _qLocalServer.setSocketOptions(QLocalServer::UserAccessOption);
    connect(&_qLocalServer, &QLocalServer::newConnection, this, &ILocalServer::newConnection);
}

void LocalServer::close()
{
    _qLocalServer.close();
}

bool LocalServer::listen()
{
#ifndef Q_OS_WIN
    auto fullServerName = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first() + QDir::separator() + _serverName;
#else
    auto fullServerName = _serverName;
#endif
    if (!QLocalServer::removeServer(fullServerName))
        qWarning("LocalServer: could not cleanup socket");
    auto status = _qLocalServer.listen(fullServerName);
    qDebug() << "LocalServer: socket created at " << _qLocalServer.fullServerName();
    return status;
}

bool LocalServer::isListening() const
{
    return _qLocalServer.isListening();
}

shared_ptr<ILocalSocket> LocalServer::nextPendingConnection()
{
    QLocalSocket* qLocalSocket = _qLocalServer.nextPendingConnection();
    if (qLocalSocket->isValid())
    {
        auto localSocket = _localSocketFactory.create();
        localSocket->setQLocalSocket(qLocalSocket);
        return localSocket;
    }
    return nullptr;
}

QString LocalServer::serverSocketFilePath() const
{
    return _qLocalServer.fullServerName();
}

LocalServerFactory::LocalServerFactory(ILocalSocketFactory& localSocketFactory) : _localSocketFactory(localSocketFactory)
{
}

std::shared_ptr<ILocalServer> LocalServerFactory::create(const QString& serverName)
{
    return std::make_shared<LocalServer>(_localSocketFactory, serverName);
}
