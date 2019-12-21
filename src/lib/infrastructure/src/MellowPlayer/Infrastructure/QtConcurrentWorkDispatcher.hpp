#pragma once

#include <MellowPlayer/Domain/IWorkDispatcher.hpp>
#include <QMutex>
#include <QObject>
#include <QTimer>

namespace MellowPlayer::Infrastructure
{
    class QtConcurrentWorkDispatcher : public QObject, public Domain::IWorkDispatcher
    {
        Q_OBJECT
    public:
        QtConcurrentWorkDispatcher();
        void invoke(const std::function<void(void)>& workerFunction) override;
        void delayInvoke(int delayMilliseconds, const std::function<void(void)>& workerFunction) override;

    private slots:
        void onTimeout();

    private:
        QMutex _mutex;
        QTimer _timer;
        std::function<void(void)> delayedWorkerFunction;
    };
}
