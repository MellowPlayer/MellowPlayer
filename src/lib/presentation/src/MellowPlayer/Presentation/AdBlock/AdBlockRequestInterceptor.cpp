#include "AdBlockRequestInterceptor.hpp"
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

AdBlockRequestInterceptor::AdBlockRequestInterceptor(Settings& settings)
    : _logger(Loggers::logger("AdBlockRequestInterceptor")),
      _isAdBlockEnabled(settings.get(SettingKey::ADBLOCK_ENABLED))
{
}

void AdBlockRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (!_isAdBlockEnabled.value().toBool())
        return;

    auto host = info.requestUrl().host();

    for (const auto &deniedHost : _blocklist) {
        if (host.contains(deniedHost)) {
            LOG_DEBUG(_logger, "Blocking " + host + " because denied host " + deniedHost);
            info.block(true);
            return;
        }
    }

    LOG_DEBUG(_logger, "Not blocking: " + host);
}

void AdBlockRequestInterceptor::block(QString hostname)
{
    if (hostname.isEmpty()) return;

    LOG_INFO(_logger, "Add block rule to hostname " + hostname)
    _blocklist.insert(hostname);
}
