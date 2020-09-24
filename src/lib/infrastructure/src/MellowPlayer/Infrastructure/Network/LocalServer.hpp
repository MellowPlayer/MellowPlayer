#pragma once

#include <QObject>
#include <QtNetwork/QLocalServer>
#include <boost-di-extensions/Factory.hpp>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class ILocalSocket;
    class ILocalSocketFactory;

    class ILocalServer : public QObject
    {
        Q_OBJECT
    public:
        virtual void close() = 0;
        virtual bool listen() = 0;
        virtual bool isListening() const = 0;
        virtual std::shared_ptr<ILocalSocket> nextPendingConnection() = 0;
        virtual QString serverSocketFilePath() const = 0;

    signals:
        void newConnection();
    };

    class LocalServer : public ILocalServer
    {
    public:
        LocalServer(ILocalSocketFactory& localSocketFactory, const QString& serverName);

        void close() override;
        bool listen() override;
        bool isListening() const override;
        std::shared_ptr<ILocalSocket> nextPendingConnection() override;
        QString serverSocketFilePath() const override;

    private:
        ILocalSocketFactory& _localSocketFactory;
        QString _serverName;
        QLocalServer _qLocalServer;
    };

    class ILocalServerFactory
    {
    public:
        virtual ~ILocalServerFactory() = default;

        virtual std::shared_ptr<ILocalServer> create(const QString& serverName) = 0;
    };

    class LocalServerFactory : public ILocalServerFactory
    {
    public:
        explicit LocalServerFactory(ILocalSocketFactory& localSocketFactory);

        std::shared_ptr<ILocalServer> create(const QString& serverName) override;

    private:
        ILocalSocketFactory& _localSocketFactory;
    };
}
