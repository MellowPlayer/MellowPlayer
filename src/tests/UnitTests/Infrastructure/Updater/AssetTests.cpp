#include <MellowPlayer/Infrastructure/Updater/Asset.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("asset validity can be tested")
{
    GIVEN("an asset with a valid asset name and an invalid url")
    {
        Asset asset("MellowPlayer_Setup.exe", "");

        REQUIRE(asset.name() == "MellowPlayer_Setup.exe");
        REQUIRE(asset.url() == "");

        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("an asset with an valid asset name and a valid url")
    {
        Asset asset("MellowPlayer.zip",
                    "https://github.com/ColinDuquesnoy/"
                    "MellowPlayer/releases/download/2.95.0/"
                    "MellowPlayer.zip");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("an dmg asset with a valid url")
    {
        Asset asset("MellowPlayer.dmg",
                    "https://github.com/ColinDuquesnoy/"
                    "MellowPlayer/releases/download/2.95.0/"
                    "MellowPlayer.dmg");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns True")
            {
                REQUIRE(isValid);
            }
        }
    }

    GIVEN("an WindowsInstaller asset with a valid url")
    {
        Asset asset("MellowPlayer_Setup.exe",
                    "https://github.com/ColinDuquesnoy/"
                    "MellowPlayer/releases/download/"
                    "2.95.0/MellowPlayer_Setup.exe");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns True")
            {
                REQUIRE(isValid);
            }
        }
    }
}

SCENARIO("Asset type is queryable")
{
    GIVEN("3 different asset types")
    {
        Asset dmgAsset("MellowPlayer.dmg",
                       "https://github.com/ColinDuquesnoy/"
                       "MellowPlayer/releases/download/2.95.0/"
                       "MellowPlayer.dmg");
        Asset windowsInstallerAsset("MellowPlayer_Setup.exe",
                                    "https://github.com/ColinDuquesnoy/"
                                    "MellowPlayer/releases/download/2.95.0/"
                                    "MellowPlayer_Setup.exe");

        WHEN("querying windowsInstaller asset type")
        {
            bool isWindowsInstaller = windowsInstallerAsset.isWindowsInstaller();
            bool isDmg = windowsInstallerAsset.isDmg();

            THEN("isWindowsInstaller is True")
            {
                REQUIRE(isWindowsInstaller);
            }
            THEN("isDmg is False")
            {
                REQUIRE(!isDmg);
            }
        }

        WHEN("querying dmg asset type")
        {
            bool isWindowsInstaller = dmgAsset.isWindowsInstaller();
            bool isDmg = dmgAsset.isDmg();

            THEN("isWindowsInstaller is False")
            {
                REQUIRE(!isWindowsInstaller);
            }
            THEN("isDmg is True")
            {
                REQUIRE(isDmg);
            }
        }
    }
}