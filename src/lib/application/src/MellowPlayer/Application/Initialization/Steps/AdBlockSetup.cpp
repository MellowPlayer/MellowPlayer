#include "AdBlockSetup.hpp"
#include <QStandardPaths>
#include <QWebEngineProfile>
#include <MellowPlayer/Infrastructure/AdBlock/IFileBlockListLoader.hpp>
#include <MellowPlayer/Infrastructure/AdBlock/IHttpBlockListLoader.hpp>

using namespace MellowPlayer::Application;

AdBlockSetup::AdBlockSetup(
        std::unique_ptr<Presentation::IAdBlockRequestInterceptor> interceptor,
        Infrastructure::IFileBlockListLoader& fileLoader,
        Infrastructure::IHttpBlockListLoader& httpLoader)
    : _interceptor(std::move(interceptor)),
      _fileLoader(fileLoader),
      _httpLoader(httpLoader)
{
}

void AdBlockSetup::initialize(const ResultCallback &resultCallback)
{
    const auto callback = [&](const auto blocklist) {
        for (const auto& hostname : blocklist) {
            _interceptor->block(hostname);
        }
    };

    // Peter Lowe's adservers list, source: https://pgl.yoyo.org/adservers/
    const auto peterLoweListUrl =
            "https://pgl.yoyo.org/adservers/serverlist.php?hostformat=nohtml&showintro=0";
    _httpLoader.load(peterLoweListUrl, callback);

    // User file's blocklist
    const auto userFilePath = QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                                     "blocklist.txt");
    _fileLoader.load(userFilePath, callback);

    auto profile = QWebEngineProfile::defaultProfile();
    profile->setRequestInterceptor(_interceptor.get());
    resultCallback(true);
}
