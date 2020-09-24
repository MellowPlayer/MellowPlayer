#include <MellowPlayer/Infrastructure/Application/Application.hpp>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <QDebug>
#include <QProcess>

using namespace std;
using namespace MellowPlayer::Infrastructure;

Application::Application(IQtApplication& qtApplication, const std::shared_ptr<ApplicationNetworkProxy>& applicationNetworkProxy)
        : _qtApp(qtApplication), _applicationNetworkProxy(applicationNetworkProxy), _restartRequested(false)
{
    connect(&_qtApp, &IQtApplication::commitDataRequest, this, &Application::commitDataRequest);
}

void Application::initialize()
{
    emit initialized();
}

int Application::run()
{
    emit started();
    auto returnCode = _qtApp.run();
    emit finished();

    if (_restartRequested)
    {
        qWarning() << "restarting application...";
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }

    return returnCode;
}

void Application::quit(int returnCode)
{
    _qtApp.exit(returnCode);
}

void Application::restart()
{
    _restartRequested = true;
    quit();
}

void Application::restoreWindow()
{
    emit restoreWindowRequest();
}
