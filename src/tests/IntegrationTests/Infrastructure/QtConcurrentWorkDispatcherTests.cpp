#include <MellowPlayer/Infrastructure/System/QtConcurrentWorkDispatcher.hpp>
#include <QtTest/qtestsystem.h>
#include <catch2/catch.hpp>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;
using namespace MellowPlayer::Infrastructure;

TEST_CASE("QtConcurrentWorkDispatcherTests")
{
    QtConcurrentWorkDispatcher workDispatcher;

    SECTION("invoke")
    {
        bool finished = false;
        workDispatcher.invoke([&]() { finished = true; });
        sleep_for(milliseconds(100));
        REQUIRE(finished);
    }

    SECTION("delayInvoke")
    {
        bool finished = false;
        workDispatcher.delayInvoke(10, [&]() { finished = true; });
        QTest::qWait(100);
        REQUIRE(finished);
    }
}
