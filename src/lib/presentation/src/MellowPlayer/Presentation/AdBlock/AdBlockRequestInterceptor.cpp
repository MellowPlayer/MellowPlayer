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
    const auto url = info.requestUrl();
    LOG_DEBUG(_logger, "Request: " + url.toString());

    if (!_isAdBlockEnabled.value().toBool())
        return;

    bool shouldBlock = isBlocked(url);
    info.block(shouldBlock);

    LOG_DEBUG(_logger, (shouldBlock ? "Blocked: " : "Not blocked: ") + url.host());
}

void AdBlockRequestInterceptor::block(QString hostname)
{
    if (hostname.isEmpty()) return;

    _blocklist.insert(hostname);
}

bool AdBlockRequestInterceptor::isBlocked(QUrl url) const
{
    if (url.path().contains("pagead") || url.path().contains("ads"))
        return true;

    const auto hostname = url.host();

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
