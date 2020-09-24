#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/HiDPISupport.h>
#include <QtCore>
#include <QGuiApplication>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

HiDPISupport::HiDPISupport(const QString &organizationName) : _organizationName(organizationName)
{
}

void HiDPISupport::configure()
{
    QSettings settings(_organizationName, "3");
    bool automaticScaling = settings.value(SettingKey::toString(SettingKey::APPEARANCE_AUTO_HIDPI_SCALING), false).toBool();

    if (qgetenv("QT_AUTO_SCREEN_SCALE_FACTOR").isEmpty())
    {
        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", automaticScaling ? "1" : "0");
        QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    }

    if (qgetenv("QT_SCALE_FACTOR").isEmpty() && !automaticScaling)
    {
        auto factor = settings.value(SettingKey::toString(SettingKey::APPEARANCE_HIDPI_SCALING_FACTOR), 100).toInt() / 100.0;
        qputenv("QT_SCALE_FACTOR", QString::number(factor).toLocal8Bit());
    }
}
