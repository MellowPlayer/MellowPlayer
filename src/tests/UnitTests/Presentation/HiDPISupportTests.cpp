#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/HiDPISupport.h>
#include <QSettings>
#include <Utils/DependencyPool.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SCENARIO("HiDPI Support")
{
    QString orgName = "MellowPlayer.Tests";
    QSettings settings(orgName, "3");
    HiDPISupport hiDPISupport(orgName);

    GIVEN("No scaling environment variable is set and automatic scaling is ON and scaling factor is set to 2.5")
    {
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "");
        qputenv("QT_SCALE_FACTOR", "");

        settings.setValue(SettingKey::toString(SettingKey::APPEARANCE_AUTO_HIDPI_SCALING), true);
        settings.setValue(SettingKey::toString(SettingKey::APPEARANCE_HIDPI_SCALING_FACTOR), 250);

        WHEN("configure is called")
        {
            hiDPISupport.configure();

            THEN("QT_AUTO_SCREEN_SCALE_FACTOR is set to 1")
            {
                REQUIRE(qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR").toStdString() == "1");
            }

            AND_THEN("QT_SCALE_FACTOR is left empty")
            {
                REQUIRE(qgetenv("QT_SCALE_FACTOR").toStdString() == "");
            }
        }
    }

    GIVEN("No scaling environment variable is set and automatic scaling is OFF and scaling factor is set to 2.5")
    {
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "");
        qputenv("QT_SCALE_FACTOR", "");

        settings.setValue(SettingKey::toString(SettingKey::APPEARANCE_AUTO_HIDPI_SCALING), false);
        settings.setValue(SettingKey::toString(SettingKey::APPEARANCE_HIDPI_SCALING_FACTOR), 250);

        WHEN("configure is called")
        {
            hiDPISupport.configure();

            THEN("QT_AUTO_SCREEN_SCALE_FACTOR is set to 0")
            {
                REQUIRE(qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR").toStdString() == "0");
            }

            AND_THEN("QT_SCALE_FACTOR is set to 2.5")
            {
                REQUIRE(qgetenv("QT_SCALE_FACTOR").toStdString() == "2.5");
            }
        }
    }

    GIVEN("scaling environment variables are set and automatic scaling is OFF and scaling factor is set to 2.5")
    {
        QByteArray initialAutoScaling("1");
        QByteArray initialScalingFactor("1.5");
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", initialAutoScaling);
        qputenv("QT_SCALE_FACTOR", initialScalingFactor);

        settings.setValue(SettingKey::toString(SettingKey::APPEARANCE_AUTO_HIDPI_SCALING), false);
        settings.setValue(SettingKey::toString(SettingKey::APPEARANCE_HIDPI_SCALING_FACTOR), 250);

        WHEN("configure is called")
        {
            hiDPISupport.configure();

            THEN("QT_AUTO_SCREEN_SCALE_FACTOR initial value is retained")
            {
                REQUIRE(qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR").toStdString() == initialAutoScaling.toStdString());
            }

            AND_THEN("QT_SCALE_FACTOR initial value is retained")
            {
                REQUIRE(qgetenv("QT_SCALE_FACTOR").toStdString() == initialScalingFactor.toStdString());
            }
        }
    }
}