#pragma once

#include <QObject>
#include <QString>

namespace MellowPlayer::Infrastructure
{
    class Release;
    class IFileDownloader;

    class AbstractPlatformUpdater : public QObject
    {
        Q_OBJECT
    public:
        explicit AbstractPlatformUpdater(IFileDownloader& fileDownloader);

        virtual void setRelease(const Release* release);
        void download();
        void install();
        virtual void restart(){};

        virtual bool canInstall() const = 0;

    signals:
        void downloadFinished(bool success);
        void installFinished(bool success);
        void progressUpdated(double progress);

    protected:
        virtual void doInstall(const QString& assetFilePath) = 0;
        virtual QString assetUrl() const = 0;
        virtual QString assetFileName() const = 0;

        const Release* _release = nullptr;

    private:
        QString makeDestinationPath();

        QString _assetFilePath;
        IFileDownloader& _fileDownloader;
    };
}
