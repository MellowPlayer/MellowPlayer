#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <QFileSystemWatcher>
#include <QMap>

namespace MellowPlayer::Domain
{
    class ILogger;
    class StreamingService;
}

namespace MellowPlayer::Infrastructure
{
    class StreamingServiceWatcher : public Domain::IStreamingServiceWatcher
    {
        Q_OBJECT
    public:
        StreamingServiceWatcher();

        void watch(Domain::StreamingService& serviceToWatch) override;

    private slots:
        void onFileChanged(const QString& path);

    private:
        void watchPath(const QString& path);

        class PluginInfo : public QObject
        {
        public:
            Domain::StreamingService& _service;
            QString _scriptPath;
            QString _themePath;

            PluginInfo(Domain::StreamingService& service, QString scriptPath, QString themePath, QObject* parent);
        };

        Domain::ILogger& _logger;
        QMap<QString, PluginInfo*> _pluginInfo;
        QFileSystemWatcher _fileSystemWatcher;
    };
}
