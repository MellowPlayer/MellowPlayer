#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Presentation;

CacheViewModel::CacheViewModel(IContextProperties& contextProperties) : ContextProperty("_cache", this, contextProperties)
{
}

void CacheViewModel::clear()
{
    // clear http cache
    auto& profile = *QWebEngineProfile::defaultProfile();
    profile.clearHttpCache();

    // clear mellowplayer cache (covers,...)
    for (auto dir : QStandardPaths::standardLocations(QStandardPaths::CacheLocation))
    {
        QDir cacheDir(dir);
        qDebug() << "removing cache directory: " << dir;
        cacheDir.removeRecursively();
    }
}
