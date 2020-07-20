#include "FileBlockListLoader.hpp"
#include <MellowPlayer/Infrastructure/System/TextFile.hpp>

using namespace MellowPlayer::Infrastructure;

FileBlockListLoader::FileBlockListLoader()
{
}

void FileBlockListLoader::load(QString path, const std::function<void (QList<QString>)> callback) const
{
    TextFile file(path);

    if (file.exists()) {
        QString content = file.read();
        QList<QString> blocklist;
        for (const auto& hostname : content.split('\n')) {
            // if line starts with '#' it is a comment
            if (hostname.isEmpty() || hostname.startsWith("#"))
                continue;
            blocklist.append(hostname);
        }
        callback(blocklist);
    } else {
        callback(QList<QString>());
    }
}
