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
    bool shouldBlock = isBlocked(host);
    info.block(shouldBlock);

    LOG_DEBUG(_logger, (shouldBlock ? "Blocked: " : "Not blocked: ") + host);
}

void AdBlockRequestInterceptor::block(QString hostname)
{
    if (hostname.isEmpty()) return;

    _blocklist.insert(hostname);
}

bool AdBlockRequestInterceptor::isBlocked(QString hostname) const
{
    // find if the hostname is in the blocklist
    if (_blocklist.contains(hostname))
        return true;

    for (const auto& blockedHost : _blocklist) {
        // find if the hostname is a subdomain of a hostname in the blocklist
        if (hostname.endsWith("." + blockedHost)) {
            return true;
        }
    }

    return false;
}
