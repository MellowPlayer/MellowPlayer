#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <QDebug>
#include <QDir>
#include <QWebEngineProfile>

using namespace MellowPlayer::Presentation;

CookiesViewModel::CookiesViewModel(IContextProperties& contextProperties) : ContextProperty("_cookies", this, contextProperties)
{
}

void CookiesViewModel::clear()
{
    auto& profile = *QWebEngineProfile::defaultProfile();
    QDir storageDir(profile.persistentStoragePath());
    qDebug() << "removing persistent storage directory: " << storageDir;
    storageDir.removeRecursively();
}
