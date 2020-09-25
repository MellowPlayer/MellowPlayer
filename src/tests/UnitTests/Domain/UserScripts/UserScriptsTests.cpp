#include <Fakes/FakeSettingsStore.hpp>
#include <Fakes/FakeUserScript.hpp>
#include <Fakes/FakeUserScriptFactory.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/UserScripts/UserScripts.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

#ifdef QT_DEBUG
SCENARIO("UserScriptsTests")
{
    FakeUserScriptFactory userScriptFactory { "code", "/path", "name" };
    QString serviceName = "fakeService";
    FakeSettingsStore settingsStore;
    settingsStore.clear();

    GIVEN("empty settings")
    {
        UserScripts userScripts(serviceName, userScriptFactory, settingsStore);

        WHEN("get count")
        {
            THEN("count is zero")
            {
                REQUIRE(userScripts.count() == 0);
            }
        }

        WHEN("add script")
        {
            userScripts.add("name", "/path");

            THEN("count is 1")
            {
                REQUIRE(userScripts.count() == 1);

                AND_THEN("settings are saved")
                {
                    REQUIRE(settingsStore.value("fakeService/userScriptPaths", QStringList()).toStringList().count() == 1);
                    REQUIRE(settingsStore.value("fakeService/userScriptNames", QStringList()).toStringList().count() == 1);
                }
            }

            AND_WHEN("remove is called")
            {
                userScripts.remove("name");

                THEN("file is removed")
                {
                    REQUIRE(userScriptFactory.lastCreated()->removed());
                }

                THEN("count is zero")
                {
                    REQUIRE(userScripts.count() == 0);

                    AND_THEN("settings paths count is 0")
                    {
                        REQUIRE(settingsStore.value("fakeService/userScriptPaths", QVariant()).toStringList().count() == 0);
                    }

                    AND_THEN("settings names count is 0")
                    {
                        REQUIRE(settingsStore.value("fakeService/userScriptNames", QVariant()).toStringList().count() == 0);
                    }
                }
            }
        }
    }

    GIVEN("2 scripts in settings")
    {
        QStringList paths;
        paths << "/path2";
        paths << "/path2";
        settingsStore.setValue("fakeService/userScriptPaths", paths);

        QStringList names;
        names << "name1";
        names << "name2";
        settingsStore.setValue("fakeService/userScriptNames", names);

        WHEN("creating a UserScripts instance")
        {
            UserScripts userScripts(serviceName, userScriptFactory, settingsStore);

            THEN("Two user scripts are available")
            {
                REQUIRE(userScripts.count() == 2);
            }
        }
    }
}
#endif
