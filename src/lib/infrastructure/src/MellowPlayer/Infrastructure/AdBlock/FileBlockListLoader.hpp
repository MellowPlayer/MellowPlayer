#pragma once

#include <QObject>
#include <MellowPlayer/Infrastructure/AdBlock/IFileBlockListLoader.hpp>

namespace MellowPlayer::Infrastructure
{
    class FileBlockListLoader : public Infrastructure::IFileBlockListLoader
    {
        Q_OBJECT
    public:
        explicit FileBlockListLoader();

        void load(QString path, const std::function<void (QList<QString>)>) const override;
    };
}
