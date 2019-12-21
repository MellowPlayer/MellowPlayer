#include "Utils/DependencyPool.hpp"
#include <Fakes/FakeBinTrayHttpClient.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <MellowPlayer/Infrastructure/Updater/UpdateChannel.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("check for stable updates")
{
    MellowPlayer::Tests::DependencyPool pool;
    Settings& settings = pool.getSettings();
    settings.get(SettingKey::MAIN_UPDATE_CHANNEL).setValue((int) UpdateChannel::Stable);

    GIVEN("current version is 2.2.4 from April 2017")
    {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        Updater& updater = pool.getUpdater();
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        REQUIRE(updater.status() == Updater::Status::None);

        WHEN("check for updates")
        {
            updater.check();

            THEN("update to version version 3.4.0 is available")
            {
                REQUIRE(updater.status() == Updater::Status::UpdateAvailable);
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.latestRelease()->name() == "3.4.0");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 3.5.0 from December 2018")
    {
        Release currentRelease("3.5.0", QDate::fromString("2018-12-28", Qt::ISODate));
        Updater& updater = pool.getUpdater();
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates")
        {
            updater.check();

            THEN("no update is available")
            {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.latestRelease() == nullptr);
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }

    GIVEN("current version is 3.5.90 from July 2019")
    {
        Release currentRelease("3.5.90", QDate::fromString("2019-07-01", Qt::ISODate));
        Updater& updater = pool.getUpdater();
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates")
        {
            updater.check();

            THEN("no update is available")
            {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.latestRelease() == nullptr);
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }
}

SCENARIO("check for Continuous updates")
{
    FakeBinTrayHttpClient fakeHttpClient;
    LatestBinTrayRelease querier(fakeHttpClient);
    MellowPlayer::Tests::DependencyPool pool;
    Settings& settings = pool.getSettings();
    settings.get(SettingKey::MAIN_UPDATE_CHANNEL).setValue((int) UpdateChannel::Continuous);

    GIVEN("current version is 2.2.4 from April 2017")
    {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        Updater& updater = pool.getUpdater();
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates")
        {
            updater.check();

            THEN("update to version version Continuous is available")
            {
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.latestRelease()->name().toStdString() == "3.4.90");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 2.95.0 from day before latest continuous")
    {
        Release currentRelease("2.95.0", QDate::fromString("2017-07-14", Qt::ISODate));
        Updater& updater = pool.getUpdater();
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates")
        {
            updater.check();

            THEN("update to Continuous is available")
            {
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.latestRelease()->name().toStdString() == "3.4.90");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 3.4.91 from day after latest continuous")
    {
        Release currentRelease("3.4.91", QDate::fromString("2018-12-03", Qt::ISODate));
        Updater& updater = pool.getUpdater();
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates")
        {
            updater.check();

            THEN("no update is available")
            {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.latestRelease() == nullptr);
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }
}
