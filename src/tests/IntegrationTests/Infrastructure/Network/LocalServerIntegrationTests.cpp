#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <QtTest/qtestsystem.h>
#include <catch2/catch.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

SCENARIO("LocalServer and LocalSocket integration tests")
{
    GIVEN("A local server and a local socket")
    {
        QString serverName = "MellowPlayerLocalServerIntegrationTests";
        LocalSocketFactory factory;
        LocalServer server(factory, serverName);
        server.listen();

        REQUIRE(server.isListening());
        REQUIRE(!server.serverSocketFilePath().isEmpty());

        LocalSocket socket;
        shared_ptr<ILocalSocket> newConnection = nullptr;
        QObject::connect(&server, &ILocalServer::newConnection, [&]() { newConnection = server.nextPendingConnection(); });

        WHEN("I connect the socket to the server")
        {
            socket.connectToServer(serverName, QIODevice::WriteOnly);

            QTest::qWait(100);

            THEN("a new connection has been received")
            {
                REQUIRE(newConnection != nullptr);
            }

            AND_WHEN("writing on the socket")
            {
                QString receivedData;

                QObject::connect(newConnection.get(), &ILocalSocket::readyRead, [&]() { receivedData = newConnection->readAll(); });
                socket.write("foo\n");

                QTest::qWait(100);

                THEN("data is received on the server")
                {
                    REQUIRE(receivedData == "foo\n");
                }

                AND_WHEN("I disconnect the socket from server")
                {
                    socket.disconnectFromServer();

                    THEN("I cannot write to the socket")
                    {
                        REQUIRE_THROWS(socket.write("data"));
                    }
                }
            }

            AND_WHEN("I close the server")
            {
                server.close();

                REQUIRE(!server.isListening());
            }
        }
    }
}
