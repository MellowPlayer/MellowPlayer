#pragma once

#include "FakeLocalSocket.hpp"
#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeLocalServer : public ILocalServer
    {
    public:
        virtual ~FakeLocalServer()
        {
            close();
        }

        void close() override
        {
            closed = true;
        }

        bool listen() override
        {
            isListening_ = true;
            return true;
        }

        bool isListening() const override
        {
            return _isListening;
        }

        QString serverSocketFilePath() const override
        {
            return "";
        }

        std::unique_ptr<ILocalSocket> nextPendingConnection() override
        {
            auto socket = std::make_unique<FakeLocalSocket>();
            newConnectionSocket = socket.get();
            return socket;
        }

        bool closed = false;
        FakeLocalSocket* newConnectionSocket;

    private:
        bool isListening_ = false;
    };

    class FakeLocalServerFactory : public ILocalServerFactory
    {
    public:
        std::shared_ptr<ILocalServer> create(QString&&) const override
        {
            auto localServer = std::make_shared<FakeLocalServer>();

            auto nonConstThis = const_cast<FakeLocalServerFactory*>(this);
            nonConstThis->lastServerCreated = localServer.get();

            return localServer;
        }

        FakeLocalServer* lastServerCreated;
    };
}
