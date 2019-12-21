#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>
#include <QtCore/QMap>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

QString UpdaterStatusConverter::toString(Updater::Status status)
{
    static QMap<Updater::Status, QString> map = {{Updater::Status::None, _strings.none()},
                                                 {Updater::Status::Checking, _strings.checking()},
                                                 {Updater::Status::UpdateAvailable, _strings.updateAvailable()},
                                                 {Updater::Status::Downloading, _strings.downloading()},
                                                 {Updater::Status::Installing, _strings.installing()},
                                                 {Updater::Status::Installed, _strings.installed()},
                                                 {Updater::Status::Failure, _strings.failure()}};

    return map[status];
}

Updater::Status UpdaterStatusConverter::fromString(const QString& string)
{
    static QMap<QString, Updater::Status> map = {{_strings.none(), Updater::Status::None},
                                                 {_strings.checking(), Updater::Status::Checking},
                                                 {_strings.updateAvailable(), Updater::Status::UpdateAvailable},
                                                 {_strings.downloading(), Updater::Status::Downloading},
                                                 {_strings.installing(), Updater::Status::Installing},
                                                 {_strings.installed(), Updater::Status::Installed},
                                                 {_strings.failure(), Updater::Status::Failure}};

    if (map.contains(string))
        return map[string];
    return Updater::Status::None;
}
