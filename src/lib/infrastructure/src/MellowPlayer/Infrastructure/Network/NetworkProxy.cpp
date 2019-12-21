#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>

using namespace MellowPlayer::Infrastructure;

NetworkProxy::NetworkProxy(const QVariantMap& qVariantMap)
        : _isEnabled(qVariantMap["enabled"].toBool()), _hostName(qVariantMap["hostName"].toString()), _port(qVariantMap["port"].toInt())
{
}

bool NetworkProxy::isEnabled() const
{
    return _isEnabled;
}

void NetworkProxy::setEnabled(bool value)
{
    if (_isEnabled != value)
    {
        _isEnabled = value;
        emit enabledChanged();
        emit changed();
    }
}

QString NetworkProxy::hostName() const
{
    return _hostName;
}

void NetworkProxy::setHostName(const QString& value)
{
    if (hostName() != value)
    {
        _hostName = value;
        emit hostNameChanged();
        emit changed();
    }
}

int NetworkProxy::port() const
{
    return _port;
}

void NetworkProxy::setPort(int value)
{
    if (port() != value)
    {
        _port = value;
        emit portChanged();
        emit changed();
    }
}

QVariantMap NetworkProxy::toQVariantMap() const
{
    QVariantMap qVariantMap;

    qVariantMap["enabled"] = _isEnabled;
    qVariantMap["port"] = _port;
    qVariantMap["hostName"] = _hostName;

    return qVariantMap;
}

QNetworkProxy NetworkProxy::create() const
{
    if (isValid())
        return QNetworkProxy(QNetworkProxy::HttpProxy, _hostName, static_cast<quint16>(_port));
    return QNetworkProxy();
}

bool NetworkProxy::isValid() const
{
    return _isEnabled && !_hostName.isEmpty() && _port != 0;
}

QString NetworkProxy::toString() const
{
    return QString("%1:%2").arg(_hostName).arg(_port);
}
