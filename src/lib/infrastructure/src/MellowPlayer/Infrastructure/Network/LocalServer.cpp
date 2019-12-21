#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

LocalServer::LocalServer(IFactory<ILocalSocket>& localSocketFactory, const QString& serverName)
        : _localSocketFactory(localSocketFactory), _serverName(serverName)
{
    QLocalServer::removeServer(serverName);
    _qLocalServer.setSocketOptions(QLocalServer::UserAccessOption);
    connect(&_qLocalServer, &QLocalServer::newConnection, this, &ILocalServer::newConnection);
}

void LocalServer::close()
{
    _qLocalServer.close();
}

bool LocalServer::listen()
{
    return _qLocalServer.listen(_serverName);
}

bool LocalServer::isListening() const
{
    return _qLocalServer.isListening();
}

unique_ptr<ILocalSocket> LocalServer::nextPendingConnection()
{
    QLocalSocket* qLocalSocket = _qLocalServer.nextPendingConnection();
    if (qLocalSocket->isValid())
    {
        unique_ptr<ILocalSocket> localSocket = _localSocketFactory.create();
        localSocket->setQLocalSocket(qLocalSocket);
        return localSocket;
    }
    return nullptr;
}

QString LocalServer::serverSocketFilePath() const
{
    return _qLocalServer.fullServerName();
}
