#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/IconSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("IconSettingViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    Setting& setting = settings.get(SettingKey::APPEARANCE_CUSTOM_TRAY_ICON);
    IconSettingViewModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue")
    {
        REQUIRE(model.value().toString() == "");
        REQUIRE(spy.count() == 0);
        model.setValue("/path/to/icon1");
        REQUIRE(model.value() == "/path/to/icon1");
        REQUIRE(spy.count() == 1);
    }

    SECTION("QML Component looks valid")
    {
        REQUIRE(model.qmlComponent().toLower().contains("icon"));
    }
}
