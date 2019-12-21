#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ListeningHistoryEntryViewModel::ListeningHistoryEntryViewModel(const ListeningHistoryEntry& entry, QObject* parent) : QObject(parent), _entry(entry)
{
}

QString ListeningHistoryEntryViewModel::songId() const
{
    return _entry.songUniqueId;
}

QString ListeningHistoryEntryViewModel::title() const
{
    return _entry.songTitle;
}

QString ListeningHistoryEntryViewModel::artist() const
{
    return _entry.artist;
}

QString ListeningHistoryEntryViewModel::artUrl() const
{
    return _entry.artUrl;
}

QString ListeningHistoryEntryViewModel::service() const
{
    return _entry.serviceName;
}

QString ListeningHistoryEntryViewModel::date() const
{
    return _dateTimeConverter.dateToString(_entry.dateTime());
}

QString ListeningHistoryEntryViewModel::time() const
{
    return _dateTimeConverter.timeToString(_entry.dateTime());
}

QString ListeningHistoryEntryViewModel::dateCategory() const
{
    return _dateTimeConverter.dateToCategory(_entry.dateTime());
}
int ListeningHistoryEntryViewModel::entryId() const
{
    return _entry.id;
}
