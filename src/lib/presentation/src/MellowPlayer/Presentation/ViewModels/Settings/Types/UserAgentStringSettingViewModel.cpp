#include <MellowPlayer/Presentation/ViewModels/Settings/Types/UserAgentStringSettingViewModel.hpp>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserAgentStringSettingViewModel::UserAgentStringSettingViewModel(Setting& setting, QObject* parent) : StringSettingViewModel(setting, parent)
{
}

QVariant UserAgentStringSettingViewModel::value() const
{
    QString value = StringSettingViewModel::value().toString();

    if (value.isEmpty())
    {
        auto& profile = *QWebEngineProfile::defaultProfile();
        value = profile.httpUserAgent();
    }

    return value;
}
