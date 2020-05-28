#include "TranslationsSetup.hpp"
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <QDirIterator>
#include <QDir>
#include <QDebug>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

TranslationsSetup::TranslationsSetup(IQtApplication& qtApplication) : _qtApplication(qtApplication)
{
}

void TranslationsSetup::initialize(const MellowPlayer::Domain::Initializable::ResultCallback& resultCallback)
{
    if (!_translator.load(QLocale(), "MellowPlayer", "_", ":/MellowPlayer/Translations"))
    {
        qWarning() << "failed to load translation: " << QLocale::system().name();
    }
    else
        qInfo() << "Translation successfully loaded: " << QLocale::system().name();

    qInfo() << "Available translations: ";
    QDirIterator it(":/MellowPlayer/Translations", QStringList() << "*.qm", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qInfo() << "  - " << it.next();

    _qtApplication.installTranslator(&_translator);

    resultCallback(true);
}
