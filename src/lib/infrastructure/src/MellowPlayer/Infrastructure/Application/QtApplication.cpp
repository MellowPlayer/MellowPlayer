#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

QtApplication::QtApplication(QApplication& application) : _qApplication(application)
{
    connect(&_qApplication, &QApplication::aboutToQuit, this, &QtApplication::aboutToQuit);
    connect(&_qApplication, &QApplication::commitDataRequest, this, &QtApplication::commitDataRequest);
}

void QtApplication::setApplicationName(QString name)
{
    _qApplication.setApplicationName(name);
}

void QtApplication::setApplicationDisplayName(QString displayName)
{
    _qApplication.setApplicationDisplayName(displayName);
}

void QtApplication::setApplicationVersion(QString version)
{
    _qApplication.setApplicationVersion(version);
}

void QtApplication::setOrganizationDomain(QString domain)
{
    _qApplication.setOrganizationDomain(domain);
}

void QtApplication::setOrganizationName(QString name)
{
    _qApplication.setOrganizationName(name);
}

void QtApplication::setWindowIcon(const QIcon& icon)
{
    _qApplication.setWindowIcon(icon);
}

int QtApplication::run()
{
    return _qApplication.exec();
}

void QtApplication::exit(int returnCode)
{
    _qApplication.exit(returnCode);
}

void QtApplication::installTranslator(QTranslator* translator)
{
    _qApplication.installTranslator(translator);
}

void QtApplication::setFont(const QFont& font)
{
    _qApplication.setFont(font);
}
