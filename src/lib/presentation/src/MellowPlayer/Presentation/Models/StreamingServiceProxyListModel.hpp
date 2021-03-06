#pragma once

#include "StreamingServiceListModel.hpp"
#include <QSortFilterProxyModel>

namespace MellowPlayer::Domain
{
    class Setting;
    class Settings;
}

namespace MellowPlayer::Presentation
{
    class StreamingServiceProxyListModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        explicit StreamingServiceProxyListModel(StreamingServiceListModel* sourceListModel, Domain::Settings& settings);

        Q_INVOKABLE void update();
        Q_INVOKABLE void setSearchText(const QString& searchText);

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
        bool lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const override;

    private slots:
        void onFavoriteChanged();
        void onActiveChanged();

    private:
        StreamingServiceListModel* _sourceListModel;
        Domain::Setting& _showFavoriteSetting;
        QString _searchText;
    };
}
