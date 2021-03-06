#include <MellowPlayer/Infrastructure/Network/HttpClient.hpp>
#include <QSignalSpy>
#include <QtTest/qtestsystem.h>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("HttpClient get github API response", "[!mayfail]")
{
    HttpClient client;

    GIVEN("an initial state and the most basic github query url")
    {
        QSignalSpy spy(&client, &HttpClient::replyReceived);

        WHEN("a get request is send")
        {
            client.get(QUrl("https://api.github.com/"));

            THEN("it receives a non empty response")
            {
                if (spy.wait(5000))
                {
                    REQUIRE(spy.count() == 1);
                    QList<QVariant> args = spy.takeFirst();
                    REQUIRE(!args.at(0).toByteArray().isEmpty());
                }
            }
        }
    }
}
