#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Helpers/Base64Helper.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

Base64Helper::Base64Helper(QObject* parent) : QObject(parent), _logger(Loggers::logger())
{
}

bool Base64Helper::isBase64(const QString& uri)
{
    return uri.contains(";base64,");
}

QImage Base64Helper::getImage(const QString& uri)
{
    LOG_DEBUG(_logger, "decoding image: " << uri);

    QImage image;
    QRegExp re("data:(image\\/.*);base64,(.*)");

    int pos = re.indexIn(uri);
    if (pos == -1)
    {
        LOG_WARN(_logger, "failed to decode base 64 image, not a valid data URI scheme...");
        return image;
    }

    QStringList captures = re.capturedTexts();
    QString format = captures.at(1).toLower();
    QString data = captures.at(2);
    LOG_DEBUG(_logger, "image format: " << format);
    LOG_DEBUG(_logger, "image data: " << data);

    QByteArray decoded = QByteArray::fromBase64(data.toUtf8());
    if (!image.loadFromData(decoded, format.toStdString().c_str()))
        LOG_WARN(_logger, "failed to load image from base64 string");

    return image;
}

bool Base64Helper::saveToFile(const QString& uri, const QString& path)
{
    QImage image = getImage(uri);

    if (!image.save(path, "PNG"))
    {
        LOG_WARN(_logger, "failed to save decoded image");
        return false;
    }

    LOG_DEBUG(_logger, "image saved to: " << path);

    return true;
}

QString Base64Helper::getImageProviderUrl(const QString& url)
{
    if (isBase64(url))
        return "base64://" + url;
    return url;
}
