#include <MellowPlayer/Presentation/Models/ListeningHistoryListModel.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>

using namespace MellowPlayer::Presentation;

ListeningHistoryProxyListModel::ListeningHistoryProxyListModel(ListeningHistoryListModel* sourceModel) : _sourceModel(sourceModel)
{
    setSourceModel(sourceModel);
    setDynamicSortFilter(true);
}

void ListeningHistoryProxyListModel::disableService(const QString& serviceName, bool disable)
{
    if (disable)
        _disabledServices.append(serviceName);
    else
        _disabledServices.removeOne(serviceName);
    invalidateFilter();
}

void ListeningHistoryProxyListModel::setSearchFilter(const QString& newSearchFilter)
{
    _searchFilter = newSearchFilter.toLower();
    invalidateFilter();
}

bool ListeningHistoryProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
    ListeningHistoryEntryViewModel* entry = _sourceModel->at(sourceRow);
    if (_disabledServices.contains(entry->service()))
        return false;
    if (_searchFilter.isEmpty())
        return true;
    else
    {
        bool titleContainsFilter = entry->title().toLower().contains(_searchFilter.toLower());
        bool artistContainsFilter = entry->artist().toLower().contains(_searchFilter.toLower());
        return titleContainsFilter || artistContainsFilter;
    }
}
