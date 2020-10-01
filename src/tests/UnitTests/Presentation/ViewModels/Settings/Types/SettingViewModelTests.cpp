#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
    BoolSettingViewModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("Basic attributes")
    {
        REQUIRE(model.type() == "bool");
        REQUIRE(!model.name().isEmpty());
        REQUIRE(model.isEnabled());
        REQUIRE(!model.toolTip().isEmpty());
    }

    SECTION("enabled should change when enableCondition is met")
    {
        Setting& dependantSetting = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
        BoolSettingViewModel dependantModel(dependantSetting, nullptr);
        QSignalSpy enabledSpy(&dependantModel, &BoolSettingViewModel::isEnabledChanged);

        REQUIRE(enabledSpy.count() == 0);
        REQUIRE(dependantModel.isEnabled());

        model.setValue(false);

        REQUIRE(enabledSpy.count() == 1);
        REQUIRE(!dependantModel.isEnabled());

        model.setValue(true);
    }
}
