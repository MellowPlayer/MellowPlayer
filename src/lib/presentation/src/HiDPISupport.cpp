#include <MellowPlayer/Presentation/HiDPISupport.h>
#include <QtCore>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

HiDPISupport::HiDPISupport(Settings& settings) : _settings(settings)
{

}

void HiDPISupport::configure()
{
    bool automaticScaling = _settings.get(SettingKey::APPEARANCE_AUTO_HIDPI_SCALING).value().toBool();
    if (qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR").isEmpty()) {
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", automaticScaling ? "1" : "0");
    }

    if ( qgetenv("QT_SCALE_FACTOR").isEmpty() && !automaticScaling) {
        auto factor = _settings.get(SettingKey::APPEARANCE_HIDPI_SCALING_FACTOR).value().toInt() / 100.0;
        qputenv("QT_SCALE_FACTOR", QString::number(factor).toLocal8Bit());
    }

    qDebug() << "QT_AUTO_SCREEN_SCALE_FACTOR=" << qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR");
    qDebug() << "QT_SCALE_FACTOR=" << qgetenv("QT_SCALE_FACTOR");
}

