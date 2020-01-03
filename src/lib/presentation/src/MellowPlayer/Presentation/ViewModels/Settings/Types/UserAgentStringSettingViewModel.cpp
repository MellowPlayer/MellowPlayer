#include <MellowPlayer/Presentation/ViewModels/Settings/Types/UserAgentStringSettingViewModel.hpp>
#include <QtWebEngineWidgets/QWebEngineProfile>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserAgentStringSettingViewModel::UserAgentStringSettingViewModel(Setting& setting, QObject* parent) : StringSettingViewModel(setting, parent)
{
}

QString UserAgentStringSettingViewModel::getValue() const
{
    QString value = StringSettingViewModel::getValue();

    if (value.isEmpty())
    {
        auto& profile = *QWebEngineProfile::defaultProfile();
        value = profile.httpUserAgent();
    }

    return value;
}
