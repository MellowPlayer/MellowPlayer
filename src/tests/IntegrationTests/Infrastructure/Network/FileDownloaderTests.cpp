#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <QSignalSpy>
#include <QTemporaryDir>
#include <QtTest/qtestsystem.h>
#include <catch2/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("FileDownloader can download a release source archive", "[!mayfail]")
{
    FileDownloader downloader;
    QTemporaryDir dir;
    QString destination = dir.path() + "/MellowPlayer.zip";
    dir.setAutoRemove(false);
    REQUIRE(!QFileInfo::exists(destination));

    QSignalSpy finishedSpy(&downloader, &FileDownloader::finished);
    QSignalSpy progressSpy(&downloader, &FileDownloader::progressChanged);

    WHEN("downloading MellowPlayer.zip from github")
    {
        downloader.download("https://github.com/ColinDuquesnoy/MellowPlayer/raw/develop/src/lib/presentation/resources/fonts/Roboto/Roboto-Black.ttf",
                            destination);

        if (finishedSpy.wait())
        {
            THEN("destination file exists")
            {
                CAPTURE(destination.toStdString());
                REQUIRE(QFileInfo::exists(destination));
                REQUIRE(QFileInfo(destination).size() != 0);
            }

            AND_THEN("progress has been updated regularly until download was finished")
            {
                REQUIRE(progressSpy.count() >= 1);
            }
        }
    }
}
