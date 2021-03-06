#include <MellowPlayer/Presentation/Converters/DateTimeConverter.hpp>
#include <QDateTime>
#include <QLocale>

using namespace MellowPlayer::Presentation;

QString DateTimeConverter::dateToCategory(const QDateTime& dateTime) const
{
    QDate date = dateTime.date();
    QDate today = QDateTime::currentDateTime().date();
    QDate yesterday = today.addDays(-1);
    QDate lastWeek = today.addDays(-7);
    QDate lastMonth = today.addMonths(-1);
    QDate lastYear = today.addYears(-1);

    if (date == today)
        return "Today";
    else if (date == yesterday)
        return "Yesterday";
    else if (date >= lastWeek)
        return "Last week";
    else if (date >= lastMonth)
        return "Last month";
    else if (date >= lastYear)
        return "Last year";
    else
        return "Years ago";
}

QString DateTimeConverter::dateToString(const QDateTime& dateTime) const
{
    return QLocale::system().toString(dateTime.date(), QLocale::ShortFormat);
}

QString DateTimeConverter::timeToString(const QDateTime& dateTime) const
{
    return QLocale::system().toString(dateTime.time(), QLocale::ShortFormat);
}
