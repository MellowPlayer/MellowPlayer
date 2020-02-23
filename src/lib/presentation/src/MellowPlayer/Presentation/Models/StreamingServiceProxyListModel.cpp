#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

StreamingServiceProxyListModel::StreamingServiceProxyListModel(StreamingServiceListModel* sourceListModel, Settings& settings)
        : _sourceListModel(sourceListModel),
          _showFavoriteSetting(settings.get(SettingKey::PRIVATE_SHOW_FAVORITE_SERVICES))
{
    setDynamicSortFilter(false);
    setSourceModel(sourceListModel);
    sort(0);

    connect(&_showFavoriteSetting, &Setting::valueChanged, this, &StreamingServiceProxyListModel::update);
}

bool StreamingServiceProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
    StreamingServiceViewModel* viewModel = _sourceListModel->at(sourceRow);

    connect(viewModel, &StreamingServiceViewModel::favoriteChanged, this, &StreamingServiceProxyListModel::update, Qt::UniqueConnection);
    connect(viewModel, &StreamingServiceViewModel::isActiveChanged, this, &StreamingServiceProxyListModel::update, Qt::UniqueConnection);

    if (viewModel->sortIndex() == -1 && _searchText.isEmpty())
        viewModel->setSortIndex(sourceRow);

    auto accepted = !_showFavoriteSetting.value().toBool() || (viewModel->isFavorite() || viewModel->isActive());

    if (_searchText.isEmpty())
        return accepted;
    else
    {
        if (accepted)
            return viewModel->name().toLower().contains(_searchText.toLower());
        return false;
    }
}

bool MellowPlayer::Presentation::StreamingServiceProxyListModel::lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const
{
    StreamingServiceViewModel* left = _sourceListModel->at(sourceLeft.row());
    StreamingServiceViewModel* right = _sourceListModel->at(sourceRight.row());

    return left->sortIndex() < right->sortIndex();
}

void StreamingServiceProxyListModel::update()
{
    invalidate();
}

void StreamingServiceProxyListModel::setSearchText(const QString& searchText)
{
    if (searchText != _searchText)
    {
        _searchText = searchText;
        update();
    }
}
