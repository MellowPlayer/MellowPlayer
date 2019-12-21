#include <MellowPlayer/Infrastructure/QtConcurrentWorkDispatcher.hpp>
#include <QtConcurrent>

using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Domain;

QtConcurrentWorkDispatcher::QtConcurrentWorkDispatcher()
{
    connect(&_timer, &QTimer::timeout, this, &QtConcurrentWorkDispatcher::onTimeout);
}

void QtConcurrentWorkDispatcher::invoke(const function<void(void)>& workerFunction)
{
    QtConcurrent::run(QThreadPool::globalInstance(), [=]() {
        QMutexLocker mutexLocker(&_mutex);
        workerFunction();
    });
}

void QtConcurrentWorkDispatcher::delayInvoke(int delayMilliseconds, const std::function<void(void)>& workerFunction)
{
    delayedWorkerFunction = workerFunction;
    _timer.stop();
    _timer.setInterval(delayMilliseconds);
    _timer.start();
}

void QtConcurrentWorkDispatcher::onTimeout()
{
    invoke(delayedWorkerFunction);
}
