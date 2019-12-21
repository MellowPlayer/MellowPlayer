#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Updater/BinTray/LatestBinTrayRelease.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QVersionNumber>

using namespace MellowPlayer::Infrastructure;

LatestBinTrayRelease::LatestBinTrayRelease(IHttpClient& httpClient) : _httpClient(httpClient)
{
    connect(&httpClient, &IHttpClient::replyReceived, this, &LatestBinTrayRelease::onReplyReceived);
}

void MellowPlayer::Infrastructure::LatestBinTrayRelease::setChannel(UpdateChannel channel)
{
    _channel = channel;
}

void MellowPlayer::Infrastructure::LatestBinTrayRelease::get()
{
    _httpClient.get(QString("https://api.bintray.com/packages/colinduquesnoy/MellowPlayer/%1/files").arg(channelToString()));
}

QString LatestBinTrayRelease::channelToString() const
{
    return UpdateChannelStringer().toString(_channel);
}

void LatestBinTrayRelease::onReplyReceived(const QByteArray& replyData)
{
    emit received(parse(replyData));
}

QString LatestBinTrayRelease::makeUrl(QString path)
{
    return QString("https://dl.bintray.com/colinduquesnoy/MellowPlayer/%1").arg(path);
}

Release* LatestBinTrayRelease::parse(const QByteArray& replyData)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(replyData);
    if (!jsonDocument.isArray())
        return nullptr;

    AssetList assets;
    auto array = jsonDocument.array();
    QString version = findLatestVersion(array);
    QDate releaseDate;
    for (int i = 0; i < array.count(); ++i)
    {
        auto file = array.at(i).toObject();

        if (file.value("version").toString() == version)
        {
            auto name = file.value("name").toString();
            auto path = file.value("path").toString();
            auto url = makeUrl(path);

            Asset asset(name, url);
            assets << asset;

            releaseDate = QDateTime::fromString(file.value("created").toString(), Qt::ISODate).date();
        }
    }
    auto releaseUrl = QString("https://bintray.com/colinduquesnoy/MellowPlayer/%1").arg(channelToString());
    auto preRelease = _channel == UpdateChannel::Continuous;
    return new Release(releaseUrl, version, releaseDate, assets, preRelease, this);
}

QString LatestBinTrayRelease::findLatestVersion(const QJsonArray& files)
{
    QVersionNumber highestVersion(0, 0, 0);

    for (int i = 0; i < files.count(); ++i)
    {
        auto file = files.at(i).toObject();
        auto version = QVersionNumber::fromString(file.value("version").toString());
        if (version > highestVersion)
            highestVersion = version;
    }

    return highestVersion.toString();
}
