#include <QtCore/QDate>
#include "FakeBinTrayHttpClient.hpp"

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

void FakeBinTrayHttpClient::get(const QString &url)
{
    if (url == "https://api.bintray.com/packages/colinduquesnoy/MellowPlayer/Continuous/files")
        emit replyReceived("[\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer_Setup.exe\",\n"
                           "    \"path\": \"continuous/3.4.90/MellowPlayer_Setup.exe\",\n"
                           "    \"version\": \"3.4.90\",\n"
                           "    \"created\": \"2018-12-02T16:17:00.501Z\"\n"
                           "  },\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer-x86_64.AppImage\",\n"
                           "    \"path\": \"continuous/3.4.90/MellowPlayer-x86_64.AppImage\",\n"
                           "    \"version\": \"3.4.90\",\n"
                           "    \"created\": \"2018-12-02T16:24:12.424Z\"\n"
                           "  },\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer_Setup.exe\",\n"
                           "    \"path\": \"continuous/3.4.89/MellowPlayer_Setup.exe\",\n"
                           "    \"version\": \"3.4.89\",\n"
                           "    \"created\": \"2018-11-02T16:17:00.501Z\"\n"
                           "  },\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer-x86_64.AppImage\",\n"
                           "    \"path\": \"continuous/3.4.89/MellowPlayer-x86_64.AppImage\",\n"
                           "    \"version\": \"3.4.89\",\n"
                           "    \"created\": \"2018-11-02T16:24:12.424Z\"\n"
                           "  }\n"
                           "]");
    else
        emit replyReceived("[\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer_Setup.exe\",\n"
                           "    \"path\": \"stable/3.4.0/MellowPlayer_Setup.exe\",\n"
                           "    \"version\": \"3.4.0\",\n"
                           "    \"created\": \"2018-07-02T16:17:00.501Z\"\n"
                           "  },\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer-x86_64.AppImage\",\n"
                           "    \"path\": \"stable/3.4.0/MellowPlayer-x86_64.AppImage\",\n"
                           "    \"version\": \"3.4.0\",\n"
                           "    \"created\": \"2018-07-02T16:24:12.424Z\"\n"
                           "  },\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer_Setup.exe\",\n"
                           "    \"path\": \"stable/3.3.0/MellowPlayer_Setup.exe\",\n"
                           "    \"version\": \"3.3.0\",\n"
                           "    \"created\": \"2017-11-02T16:17:00.501Z\"\n"
                           "  },\n"
                           "  {\n"
                           "    \"name\": \"MellowPlayer-x86_64.AppImage\",\n"
                           "    \"path\": \"stable/3.3.0/MellowPlayer-x86_64.AppImage\",\n"
                           "    \"version\": \"3.3.0\",\n"
                           "    \"created\": \"2017-11-02T16:24:12.424Z\"\n"
                           "  }\n"
                           "]");
}

QString FakeBinTrayHttpClient::expectedVersion(UpdateChannel channel)
{
    return channel == UpdateChannel::Stable ? "3.4.0" : "3.4.90";
}

QDate FakeBinTrayHttpClient::expectedDate(UpdateChannel channel)
{
    return channel == UpdateChannel ::Stable ? QDate::fromString("2018-07-02", Qt::ISODate) : QDate::fromString("2018-12-02", Qt::ISODate);
}
