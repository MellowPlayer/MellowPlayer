#pragma once

#include "../../../lib/infrastructure/src/MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp"

namespace MellowPlayer::Tests
{
    class FakePlatformUpdater : public Infrastructure::AbstractPlatformUpdater
    {
    public:
        FakePlatformUpdater(IFileDownloader& fileDownloader) : Infrastructure::AbstractPlatformUpdater(fileDownloader)
        {
        }

        bool canInstall() const override
        {
            return _canInstall;
        }

        void setCanInstall(bool enable)
        {
            _canInstall = enable;
        }

        void finishDownload()
        {
            emit downloadFinished(true);
        }

        void finishInstall()
        {
            emit installFinished(true);
        }

    protected:
        void doInstall(const QString&) override
        {
        }

        QString assetUrl() const override
        {
            return nullptr;
        }

        QString assetFileName() const override
        {
            return nullptr;
        }

    private:
        bool _canInstall = false;
    };
}