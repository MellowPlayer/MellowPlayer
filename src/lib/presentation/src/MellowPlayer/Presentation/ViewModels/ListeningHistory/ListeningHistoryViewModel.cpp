#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ListeningHistoryViewModel::ListeningHistoryViewModel(IListeningHistory& listeningHistory)
        : QmlSingleton("ListeningHistoryViewModel", this),
          _listeningHistoryService(listeningHistory),
          _sourceModel(new ListeningHistoryListModel(this, "title", "entryId")),
          _proxyModel(_sourceModel)
{
    _proxyModel.setSourceModel(_sourceModel);
}

ListeningHistoryProxyListModel* ListeningHistoryViewModel::model()
{
    return &_proxyModel;
}

void ListeningHistoryViewModel::onEntryAdded(const ListeningHistoryEntry& entry)
{
    _sourceModel->prepend(new ListeningHistoryEntryViewModel(entry, this));
}

void ListeningHistoryViewModel::onEntryRemoved(int entryId)
{
    _sourceModel->remove(_sourceModel->getByUid(QString("%1").arg(entryId)));
}

void ListeningHistoryViewModel::load()
{
    connect(&_listeningHistoryService, &ListeningHistory::entryAdded, this, &ListeningHistoryViewModel::onEntryAdded);
    connect(&_listeningHistoryService, &ListeningHistory::entryRemoved, this, &ListeningHistoryViewModel::onEntryRemoved);

    _listeningHistoryService.load();

    QList<ListeningHistoryEntryViewModel*> items;
    for (const auto& entry : _listeningHistoryService.toList())
    {
        items.prepend(new ListeningHistoryEntryViewModel(entry, this));
    }
    _sourceModel->setItems(items);
}

void ListeningHistoryViewModel::disableService(const QString& serviceName, bool disable)
{
    _proxyModel.disableService(serviceName, disable);
}

void ListeningHistoryViewModel::setSearchFilter(const QString& searchFilter)
{
    _proxyModel.setSearchFilter(searchFilter);
}

void ListeningHistoryViewModel::removeById(int id)
{
    _listeningHistoryService.removeById(id);
}

void ListeningHistoryViewModel::removeByDateCategory(const QString& dateCategory)
{
    QList<int> toRemove;
    for (int i = 0; i < _sourceModel->count(); ++i)
    {
        ListeningHistoryEntryViewModel* entry = _sourceModel->at(i);
        if (entry->dateCategory() == dateCategory)
            toRemove.append(entry->entryId());
    }
    _listeningHistoryService.removeManyById(toRemove);
}
