#include "FontsSetup.hpp"
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <QFontDatabase>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

FontsSetup::FontsSetup(IQtApplication& qtApplication) : _qtApplication(qtApplication)
{

}

void FontsSetup::initialize(const MellowPlayer::Domain::Initializable::ResultCallback& resultCallback)
{
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-ThinItalic.ttf");
    _qtApplication.setFont(QFont("Roboto"));

    resultCallback(true);
}
