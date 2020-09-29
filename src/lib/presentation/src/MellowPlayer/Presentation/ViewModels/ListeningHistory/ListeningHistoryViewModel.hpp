#pragma once

#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>
#include <MellowPlayer/Presentation/Qml/QmlSingleton.hpp>

namespace MellowPlayer::Domain
{
    class IListeningHistory;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel : public QmlSingleton
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* model READ model CONSTANT)
    public:
        ListeningHistoryViewModel(Domain::IListeningHistory& listeningHistory);

        void load();
        ListeningHistoryProxyListModel* model();

        Q_INVOKABLE void disableService(const QString& serviceName, bool disable);
        Q_INVOKABLE void setSearchFilter(const QString& searchFilter);
        Q_INVOKABLE void removeById(int entryId);
        Q_INVOKABLE void removeByDateCategory(const QString& dateCategory);

    private slots:
        void onEntryAdded(const Domain::ListeningHistoryEntry& entry);
        void onEntryRemoved(int entryId);

    private:
        Domain::IListeningHistory& _listeningHistoryService;
        ListeningHistoryListModel* _sourceModel;
        ListeningHistoryProxyListModel _proxyModel;
    };
}
