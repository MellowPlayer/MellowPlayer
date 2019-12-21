#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Presentation;

CacheViewModel::CacheViewModel(std::shared_ptr<IContextProperties> contextProperties) : ContextProperty("cache", this, contextProperties)
{
}

void CacheViewModel::clear()
{
    // clear http cache
    QWebEngineProfile profile("Default");
    profile.clearHttpCache();

    // clear mellowplayer cache (covers,...)
    for (auto dir : QStandardPaths::standardLocations(QStandardPaths::CacheLocation))
    {
        QDir cacheDir(dir);
        qInfo() << "removing cache directory: " << dir;
        cacheDir.removeRecursively();
    }
}
